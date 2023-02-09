#!/bin/env python3

license = """
/*
 * Copyright 2019-2023 Matthew Ballance and contributors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
"""

import os

def process_dir(d):
    for l in os.listdir(d):
        if l.endswith(".cpp") or l.endswith(".h"):
            has_license = False
            has_copyright = False
            content = ""
            with open(os.path.join(d, l), "r") as fp:
                # Look for a Licensed string 
                # in the first few lines of the file
                for i in range(32):
                    line = fp.readline()
                    
                    if line == "":
                        break
                
                    if line.find("Licensed") != -1:
                        has_license = True
                        break

                if not has_license:
                    fp.seek(0)
                    content = fp.read()
                    
                        
            if not has_license:
                print("Need to add license on " + l)
                
                with open(os.path.join(d, l), "w") as fp:
                    fp.write(license.strip())
                    fp.write("\n")
                    fp.write(content)
                    
        elif os.path.isdir(os.path.join(d, l)):
            process_dir(os.path.join(d, l))
    
def main():
    libvsc_dir = os.path.dirname(os.path.abspath(os.path.dirname(__file__)))
    libvsc_srcdir = os.path.join(libvsc_dir, "src")
    libvsc_testdir = os.path.join(libvsc_dir, "test")
  
    process_dir(libvsc_srcdir)
    process_dir(libvsc_testdir)
  
if __name__ == "__main__":
  main()


