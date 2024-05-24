#include "windows.h" #include "stdio.h"
const DWORD dwPrimes = 50000;    // Prosti brojevi do 50,000
DWORD TestPrimes(HANDLE hFile);
DWORD DisplayError(LPSTR strError);
int main(int argc, char* argv[])
{
    char buf[100];
    DWORD dwBytesWritten;
    HANDLE hPrimes = CreateFile(      "Primes", // Datoteka
                                      GENERIC_READ|GENERIC_WRITE, // Citanje i pisanje
                                      0, // Nema dijeljenja
                                      NULL,  // Podrazumijevana sigurnost
                                      CREATE_ALWAYS, // Kreirati
                                      FILE_FLAG_DELETE_ON_CLOSE, // Obrisati nakon kraja
                                      NULL);           // Bez uzorka
    if (hPrimes == INVALID_HANDLE_VALUE)    return DisplayError("Kreiranja");  // Napravi praznu datoteku od dwPrimes bajtova
    memset(buf,0,sizeof(buf));
    while(WriteFile(hPrimes,&buf,sizeof(buf),&dwBytesWritten,NULL))     if (GetFileSize(hPrimes,NULL)>dwPrimes) break;  // Iskoristi je za provjeru Eratostenovim sitom  TestPrimes(hPrimes);  return CloseHandle(hPrimes); // Zatvaranje datoteke }
    DWORD TestPrimes(HANDLE hFile) {
        DWORD dwBytesRead,dwBytesWritten,dwTestPrime = 2;
        BYTE byteTestByte;
        do {
            BOOL bFillMode = FALSE;
            DWORD dwPos = dwTestPrime;
            while(dwPos<dwPrimes)  {
                if (SetFilePointer(hFile,dwPos,0, FILE_BEGIN)==(DWORD)-1)        return DisplayError("Pozicioniranja");
                if (!bFillMode) { // U ovom rezimu prolazimo dok ne dodjemo do prostog broja
                    if (!ReadFile(hFile, &byteTestByte,1,&dwBytesRead,NULL))          return DisplayError ("Citanja");
                    if (byteTestByte == 0) {          // Jest!
                        printf("%d ", dwPos);
                        bFillMode = TRUE;         // Vrati se na prethodni
                        if (SetFilePointer(hFile,-1,0,FILE_CURRENT)==(DWORD)-1)            return DisplayError("Pozicioniranja");
                    }
                }
                if (bFillMode) {         //U ovom rezimu oznacavamo brojeve koje ne treba smatrati prostim ili su vec napisani
                    BYTE byteFill = 1;
                    if (!WriteFile(hFile,&byteFill,1,&dwBytesWritten,NULL))          return DisplayError("Pisanja");
                }
                dwPos+=dwTestPrime; // Skok pozicije za broj koji je proglasen prostim
            }
        } while(dwTestPrime++ < dwPrimes); // Prolaza dok ne dodjemo do kraja
        return 0;
    }
    DWORD DisplayError(LPSTR strError) {
        DWORD dwError = GetLastError();
        printf ("Greska broj %d se dogodila tokom %s ",dwError, strError);
        return dwError;
    }
