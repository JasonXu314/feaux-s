BROWSER_CXX = clang++
TESTS_CXX = g++
COMMON_FLAGS = -Wall -W -pedantic-errors
BROWSER_FLAGS = $(COMMON_FLAGS) -nostdlib --target=wasm32 -fvisibility=hidden -ffunction-sections -fdata-sections -D MEM_POLYFILL
TESTS_FLAGS = $(COMMON_FLAGS) -g
LINK_FLAGS = --no-entry --strip-all --export-dynamic --allow-undefined-file=js.sym --import-memory --global-base=16777216

MODULES = utils hardware

UTILS = $(patsubst src/utils/%.cpp, bin/modules/utils/%.o, $(wildcard src/utils/*.cpp))
HARDWARE = $(patsubst src/hardware/%.cpp, bin/modules/hardware/%.o, $(wildcard src/hardware/*.cpp))

.PHONY: integrations/* $(MODULES) clean

integrations/%.o: CXX = $(BROWSER_CXX)
integrations/%.o: FLAGS = $(BROWSER_FLAGS)
integrations/%.o: LINKER = wasm-ld
integrations/%: CXX = $(BROWSER_CXX)
integrations/%: FLAGS = $(BROWSER_FLAGS)
integrations/%: LINKER = wasm-ld

tests/%.o: CXX = $(TESTS_CXX)
tests/%.o: FLAGS = $(TESTS_FLAGS)
tests/%.o: LINKER = ld
tests/%: CXX = $(TESTS_CXX)
tests/%: FLAGS = $(TESTS_FLAGS)
tests/%: LINKER = ld

bin/modules/utils/%.o: src/utils/%.cpp $(wildcard src/utils/*.h)
	$(CXX) $(FLAGS) -c $< -o $@

utils: $(UTILS)
	$(LINKER) -r bin/modules/utils/*.o -o bin/modules/utils.o

bin/modules/hardware/%.o: src/hardware/%.cpp $(wildcard src/hardware/*.h)
	$(CXX) $(FLAGS) -c $< -o $@

hardware: $(HARDWARE)
	$(LINKER) -r bin/modules/hardware/*.o -o bin/modules/hardware.o

integrations/%.o: tests/integration/%.cpp $(MODULES)
	$(CXX) $(FLAGS) -c $< -o bin/$@

integrations/%: integrations/%.o $(MODULES)
	wasm-ld $(LINK_FLAGS) bin/$< bin/modules/*.o -o tests/integration/bin/$*.wasm

tests/%.o: tests/unit/%.cpp $(MODULES)
	$(CXX) $(FLAGS) -c $< -o bin/$@

tests/%: tests/%.o $(MODULES)
	$(CXX) $(FLAGS) bin/$< bin/modules/*.o -o tests/unit/bin/$*

clean:
	@- rm bin/modules/*.o bin/modules/**/*.o