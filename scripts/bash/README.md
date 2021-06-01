# Stress Testing
1. Name two programs you want to compare `a.cpp` and `b.cpp`, and compile both of them.
2. Write a generator `gen.cpp` and compile it.
3. Run `bash.bat`. Three new files will be created:
- `test.in` - contains the test case.
- `a.out` - contains the output from program `a`.
- `b.out` - contains the output from program `b`.
In the console, you will see the seed used for each test case. New test cases will be generated and ran indefinitely until a mismatch occurs. File comparisons are in binary mode, meaning whitespace matters.
