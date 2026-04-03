Cross-Compiling with PLCnext SDK
This project is configured to cross-compile using the PLCnext SDK for the ARM architecture. Below are the steps and configurations used to set up the development environment in Visual Studio Code (VS Code).

Prerequisites
PLCnext SDK: Ensure that the PLCnext SDK is installed at /opt/plcnext_axcf2152_sdk_2023/.
Visual Studio Code: The project requires VS Code with the C/C++ extension (ms-vscode.cpptools).
Configuration
c_cpp_properties.json
The c_cpp_properties.json file is configured to use the ARM cross-compiler provided by the PLCnext SDK. Below is the relevant configuration:

json
Copy code
{
    "configurations": [
        {
            "name": "Linux",
            "includePath": [
                "${workspaceFolder}/**",
                "/usr/include/**",
                "/opt/plcnext_axcf2152_sdk_2023/sysroots/cortexa9t2hf-neon-pxc-linux-gnueabi/usr/include/**",
                "${workspaceFolder}/src/projects/StarterKit/**"
            ],
            "defines": [],
            "compilerPath": "/opt/plcnext_axcf2152_sdk_2023/sysroots/x86_64-pokysdk-linux/usr/bin/arm-pxc-linux-gnueabi/arm-pxc-linux-gnueabi-g++",
            "cStandard": "c99",
            "cppStandard": "c++14",
            "intelliSenseMode": "gcc-arm"
        }
    ],
    "version": 4
}
Compiler Path
The compiler path is set to:

json
Copy code
"/opt/plcnext_axcf2152_sdk_2023/sysroots/x86_64-pokysdk-linux/usr/bin/arm-pxc-linux-gnueabi/arm-pxc-linux-gnueabi-g++"
This path points to the ARM cross-compiler that supports the gnueabi ABI.

IntelliSense
IntelliSense is configured to work with ARM by setting the intelliSenseMode to gcc-arm.

Additional Notes
Restart VS Code: After making changes to the c_cpp_properties.json, you may need to restart VS Code for the changes to take effect.
Include Paths: Ensure that all necessary include paths are correctly set in the includePath array to avoid missing headers during development.
Troubleshooting
If you encounter issues with missing files such as gnu/stubs-soft.h, verify that your SDK is properly installed and that the correct paths are specified in the configuration file. Also, make sure that the necessary development packages are installed on your system.