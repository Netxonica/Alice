import os
import sys
import platform
import subprocess

system = platform.system().lower()
workspace = os.getcwd()
if system == "darwin":
    cmd = ["open", os.path.join("Build", "Release", "Alice.app")]
elif system == "linux":
    cmd = [os.path.join("Build", "Release", "Alice")]
elif system == "windows":
    cmd = [os.path.join("Build", "Release", "Alice.exe")]
else:
    print(f"Unsupported platform: {system}")
    sys.exit(1)
cmd += sys.argv[1:]
if system == "windows":
    subprocess.Popen(cmd, creationflags = (0x00000008 | 0x00000200), close_fds = True)
else:
    subprocess.Popen(cmd, start_new_session = True, close_fds = True)
print(f"Launched: {' '.join(cmd)}")