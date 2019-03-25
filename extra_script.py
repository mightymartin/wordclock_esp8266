Import("env")

# please keep $SOURCE variable, it will be replaced with a path to firmware

# Generic

def on_upload(source, target, env):
    #print source, target
    #print env
    firmware_path = str(source[0])
    # do something
    # env.Execute("curl --progress-bar -X POST -F data=@" + firmware_path + " $UPLOAD_PORT")
    env.Execute("curl $UPLOAD_FLAGS -X POST -F data=@" + firmware_path + " $UPLOAD_PORT")

env.Replace(UPLOADCMD=on_upload)
