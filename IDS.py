import os
import stat
import time

def intrusionDetection(path):
    files = {} 

    while True:
        filelist = os.listdir(path)
        for fname in filelist:
            st = os.stat(path+'/'+fname)
            if not fname in files:
                # build file object
                files[fname] = {}
                files[fname]['permissions'] = st.st_mode
                files[fname]['mtime'] = st.st_mtime
                files[fname]['ctime'] = st.st_ctime
                files[fname]['timeRatio'] = 0
            else:
                if st.st_mtime != files[fname]['mtime']:
                    files[fnames]['mtime'] = st.st_mtime

                #if change times are different
                if st.st_ctime != files[fname]['ctime'] and st.st_mtime == files[fname]['mtime']:
                    #first time file has been modified 
                    if files[fname]['timeRatio'] == 0:
                        files[fname]['timeRatio'] = int(st.st_ctime - files[fname]['ctime'])

                    #if time between changes is a multiple of timeRatio[i], it is probably an intrusion
                    elif int(st.st_ctime - files[fname]['ctime']) % files[fname]['timeRatio'] == 0 :
                        f = open("permissionChanges", "a")
                        f.write("%d - " % st.st_ctime + fname + ": %o\n" % files[fname]['permissions'])
                        f.close()
                        print("File " + fname + " is being modified in a suspicious manner")
                    files[fname]['permissions'] = st.st_mode
                    files[fname]['timeRatio'] = int(st.st_ctime - files[fname]['ctime'])
                    files[fname]['ctime'] = st.st_ctime
        print("Scanning...")
        time.sleep(1)

intrusionDetection('../p1')
