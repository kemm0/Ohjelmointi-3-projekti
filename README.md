Dependencies:

Qt charts (add from maintenance tool)

OpenSSL (add from maintenance tool)
    install the OpenSSL 64-bit binaries 
    copy libcrypto-1_1-x64.dll and libssl-1.1-x64.dll files from Qt/Tools/OpenSSL/Win_x64/bin and paste them to Qt/Tools/mingwXXX_64/bin
    
apiconfig.txt
    This file must be in the root directory of the project. APICallManager reads the API keys from this file. Format of the file is KEY=VALUE. Each key
    must be defined in their own lines. Define Fingrid API key in this file as FINGRID_API_KEY=KEYHERE.
    
HOW TO RUN:

Install dependencies
Run from Qt creator
