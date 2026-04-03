# IntelliSense & Development Environment Troubleshooting

## IntelliSense Compiler Path

If IntelliSense is not working or you are getting "Unable to resolve configuration 
with compilerPath" errors, check the compiler path in `.vscode/settings.json`:
```json
"C_Cpp.default.compilerPath": "/opt/axcf2152-sdk/sysroots/x86_64-pokysdk-linux/usr/bin/arm-pxc-linux-gnueabi/arm-pxc-linux-gnueabi-g++"
```

This must match the SDK path for your target controller. Also check 
`.vscode/c_cpp_properties.json` which has the same path in two places:
```json
"includePath": [
    "/opt/axcf2152-sdk/sysroots/cortexa9t2hf-neon-pxc-linux-gnueabi/usr/include/**"
],
"compilerPath": "/opt/axcf2152-sdk/sysroots/x86_64-pokysdk-linux/usr/bin/arm-pxc-linux-gnueabi/arm-pxc-linux-gnueabi-g++"
```

## When Changing Controller Targets

Update the SDK path in both files to match the new controller's SDK directory 
under `/opt/`. Then reset IntelliSense via `Ctrl+Shift+P` → 
**C/C++: Reset IntelliSense Database**.

## Missing Generated Headers

If you see errors like: