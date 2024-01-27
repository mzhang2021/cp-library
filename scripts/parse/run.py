"""Run program on samples

Usage:
  run.py <filename> [<testname>] [--debug=<bool>]

Options:
  -h --help         Show this screen.
  --debug=<bool>    Will include the -D_GLIBCXX_DEBUG flag, which changes certain std behavior. [default: 1]
"""

from docopt import docopt

import sys
from pathlib import Path
import os
from os import path
import filecmp
import platform

CPP_COMPILE = 'g++ -std=c++20 -O2 -Wshadow -DLOCAL '
if platform.system() == 'Darwin':
    CPP_COMPILE += '-I/Users/max/ac-library '
elif platform.system() == 'Windows':
    CPP_COMPILE += '-g -Wl,--stack,268435456 -I C:/Users/maxzh/ac-library '
else:
    CPP_COMPILE += '-g -I/media/max/DATA/ac-library '

def printFile(name):
    f = open(name, 'r')
    print(f.read())
    f.close()

def trimFile(name):
    f = open(name, 'r')
    content = []
    for line in f:
        content.append(line.strip())
    f.close()
    f = open(name, 'w')
    f.write('\n'.join(content))
    f.write('\n')
    f.close()

def remove(name):
    try:
        os.remove(name)
    except:
        pass

def execute(name, ext, test, debug):
    if test is None:
        test = name

    probDir = Path(sys.path[0]) / 'testcases' / test

    # Check if all the stuff exists
    if not path.exists(os.getcwd() + '/' + name + '.' + ext):
        print("Program not found.")
        return

    if not path.exists(probDir):
        print("Test cases not found.")
        return

    # Compile the program if c++
    if ext == 'cpp':
        remove(name)
        os.system(CPP_COMPILE + ('-D_GLIBCXX_DEBUG ' if debug else '') + name + '.cpp -o ' + name)
        if not path.exists(name):
            print("Failed to compile.")
            return

    # Run on each test case (note: doesn't support TLE verdict, program just runs forever)
    print("-----------------------------------------------------------")
    tot = 0
    correct = 0
    for file in sorted(os.listdir(probDir)):
        if file.endswith('.in'):
            sample = file[:file.rfind('.in')]
            sampleFile = str(probDir / sample)
            i = len(sample) - 1
            while sample[i].isdigit():
                i -= 1
            num = sample[i+1:]
            tot += 1
            print(f"Running Sample {num}.")

            if ext == 'cpp':
                os.system('./' + name + ' < ' + str(probDir / file) + ' > temp.out')
            elif ext == 'py':
                os.system('python3 ' + name + '.py < ' + str(probDir / file) + ' > temp.out')
            else:
                print("Unknown file extension.")
                return

            # Trim white space
            trimFile('temp.out')
            trimFile(sampleFile + '.out')

            if filecmp.cmp('temp.out', sampleFile + '.out', shallow=False):
                correct += 1
                print(f"Sample {num}: AC")
            else:
                print(f"Sample {num}: WA")

                print("\nTest:")
                printFile(sampleFile + '.in')
                print("Expected:")
                printFile(sampleFile + '.out')
                print("Got:")
                printFile('temp.out')
            print("-----------------------------------------------------------")
    print(f"{correct} / {tot} correct.")
    print()

    remove('temp.out')

def main():
    arguments = docopt(__doc__)

    if '.' not in arguments['<filename>']:
        arguments['<filename>'] += '.cpp'
    name, ext = arguments['<filename>'].rsplit('.', 1)
    test = arguments['<testname>']
    execute(name, ext, test, arguments['--debug'] == '1')

if __name__ == '__main__':
    try:
        main()
    except:
        remove('temp.out')
