import urllib.request
import json

def get_version_1():
    # get recent version, use pip bump to bump the version
    req = urllib.request.Request(f'https://pypi.python.org/pypi/openmtpk/json')
    r = urllib.request.urlopen(req)

    if r.code == 200:
        t = json.loads(r.read())
        releases = t.get('releases', []) 
        if releases:
            latest_version = sorted(releases)[-1]
            bump_version = latest_version
            
            bump_version = bump_version.split('.')
            bump_version[2] = str(int(bump_version[2]) + 1)
            
            concat_version = '.'.join(bump_version)
            new_version = concat_version
            print(latest_version)


def get_version_2():
    # get recent version, use pip bump to bump the version
    with urllib.request.urlopen(f"https://pypi.python.org/pypi/openmtpk/json") as url:
        data = json.load(url)
        print(data)
        print('<------------------------------------------------------------->')
        latest_version = (data['info']['version'])
        bump_version = latest_version
        bump_version = bump_version.split('.')
        bump_version[2] = str(int(bump_version[2]) + 1)
        concat_version = '.'.join(bump_version)
        new_version = concat_version
        print(new_version)


def main():
    #get_version_1()
    get_version_2()


if __name__ == '__main__':
    main()


