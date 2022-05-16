# Source: https://gist.github.com/ecnerwala/ffc9b8c3f61e87ca043393a135d7794d

"""Download and setup problems from Competitive Companion

Usage:
  down.py prob [<name>] [--clear=<bool>]
  down.py contest [<name>... | -n <number>] [--clear=<bool>]
  down.py samples [--clear=<bool>]
  down.py echo [--clear=<bool>]

Options:
  -h --help         Show this screen.
  --clear=<bool>    Will program clear the testcases folder. [default: 1]

Contest flags:
  -n COUNT, --number COUNT   Number of problems.
"""

from docopt import docopt

import sys
import http.server
import json
from pathlib import Path
import subprocess
import re

import os
from shutil import rmtree

TEMPLATE_DIR = 'C:/Users/maxzh/cp-library/implementations/temp.cpp'

# Returns unmarshalled or None
def listen_once(*, timeout=None):
    json_data = None

    class CompetitiveCompanionHandler(http.server.BaseHTTPRequestHandler):
        def do_POST(self):
            nonlocal json_data
            json_data = json.load(self.rfile)

    with http.server.HTTPServer(('127.0.0.1', 10046), CompetitiveCompanionHandler) as server:
        server.timeout = timeout
        server.handle_request()

    if json_data is not None:
        print(f"Got data {json.dumps(json_data)}")
    else:
        print("Got no data")
    return json_data

def listen_many(*, num_items=None, timeout=None):
    if num_items is not None:
        return [listen_once(timeout=None) for _ in range(num_items)]
    res = [listen_once(timeout=None)]
    while True:
        cnd = listen_once(timeout=timeout)
        if cnd is None:
            break
        res.append(cnd)
    return res

NAME_PATTERN = re.compile(r'^[A-Z][0-9]*\b')

def get_prob_name(data, single):
    if 'USACO' in data['group'] and 'fileName' in data['input']:
        names = [data['input']['fileName'].rstrip('.in'), data['output']['fileName'].rstrip('.out')]
        if len(set(names)) == 1:
            return names[0]

    if 'Codeforces' in data['group'] and single:
        return '_'.join([i for i in data['url'].split('/') if i and i != 'problem'][-2:])

    if 'AtCoder' in data['group'] and single:
        return [i for i in data['url'].split('/') if i][-1]

    if 'CodeChef' in data['group']:
        return [i for i in data['url'].split('/') if i][-1]

    if 'SPOJ' in data['group']:
        return [i for i in data['url'].split('/') if i][-1]

    if 'UVa' in data['group']:
        return data['name'].split()[0].zfill(5)

    if 'LibreOJ' in data['group']:
        return 'loj' + [i for i in data['url'].split('/') if i][-1]

    patternMatch = NAME_PATTERN.search(data['name'])
    if patternMatch is not None:
        return patternMatch.group(0)

    return input("What name to give? ")

def save_samples(data, probDir):
    with open(probDir / 'problem.json', 'w') as f:
        json.dump(data, f)

    for i, t in enumerate(data['tests'], start=1):
        with open(probDir / f'sample{i}.in', 'w') as f:
            f.write(t['input'])
        with open(probDir / f'sample{i}.out', 'w') as f:
            f.write(t['output'])

def make_prob(data, name, single=False):
    if name is None:
        name = get_prob_name(data, single).lower()

    print(f"Creating problem {name}...")

    # Create folder 'testcases' if it doesn't already exist
    try:
        os.mkdir(Path(sys.path[0]) / 'testcases')
    except OSError:
        pass

    # Populate 'testcases' with folder titled 'name', populated with samples
    probDir = Path(sys.path[0]) / 'testcases' / name
    if os.path.exists(probDir):
        rmtree(probDir) # If there's a name conflict, destroy the old one
    os.mkdir(probDir)

    print("Saving samples...")
    save_samples(data, probDir)

    # Create file in 'current working directory' (the place where we called the program)
    fileName = os.getcwd() + '/' + name + '.cpp'
    if not os.path.exists(fileName):
        f = open(fileName, 'w')
        g = open(TEMPLATE_DIR, 'r')
        f.write(g.read())
        f.close()
        g.close()

    print()

def main():
    arguments = docopt(__doc__)

    if arguments['--clear'] == '1':
        try:
            rmtree(Path(sys.path[0]) / 'testcases')
        except:
            pass

    if arguments['echo']:
        while True:
            print(listen_once())
    elif arguments['prob']:
        data = listen_once()
        names = arguments['<name>']
        name = names[0] if names else None
        make_prob(data, name, True)
    elif arguments['contest']:
        if names := arguments['<name>']:
            datas = listen_many(num_items=len(names))
            for data, name in zip(datas, names):
                make_prob(data, name)
        elif cnt := arguments['--number']:
            cnt = int(cnt)
            datas = listen_many(num_items=cnt)
            for data in datas:
                make_prob(data, None)
        else:
            datas = listen_many(timeout=5)
            for data in datas:
                make_prob(data, None)
    elif arguments['samples']:
        data = listen_once()
        save_samples(data, Path('.'))

if __name__ == '__main__':
    main()
