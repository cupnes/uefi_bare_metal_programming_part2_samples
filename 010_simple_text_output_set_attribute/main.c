#include "efi.h"
#include "common.h"

void efi_main(void *ImageHandle __attribute__ ((unused)),
	      struct EFI_SYSTEM_TABLE *SystemTable)
{
	efi_init(SystemTable);

	puts(L" ");

	ST->ConOut->SetAttribute(ST->ConOut,
				 EFI_LIGHTGREEN | EFI_BACKGROUND_LIGHTGRAY);
	ST->ConOut->ClearScreen(ST->ConOut);

	puts(L"\r\n\r\n\r\n\r\n\r\n\r\n\r\n");
	puts(L"                              ");
	puts(L"フルスクラッチで作る!\r\n");

	ST->ConOut->SetAttribute(ST->ConOut,
				 EFI_LIGHTRED | EFI_BACKGROUND_LIGHTGRAY);
	puts(L"                           ");
	puts(L"UEFIベアメタルプログラミング\r\n");

	ST->ConOut->SetAttribute(ST->ConOut,
				 EFI_LIGHTMAGENTA | EFI_BACKGROUND_LIGHTGRAY);
	puts(L"                                    ");
	puts(L"パート2\r\n");

	ST->ConOut->SetAttribute(ST->ConOut,
				 EFI_LIGHTBLUE | EFI_BACKGROUND_LIGHTGRAY);
	puts(L"\r\n\r\n\r\n\r\n\r\n\r\n\r\n");
	puts(L"                               ");
	puts(L"大ネ申  ネ右真 著\r\n");

	ST->ConOut->SetAttribute(ST->ConOut,
				 EFI_GREEN | EFI_BACKGROUND_LIGHTGRAY);
	puts(L"\r\n\r\n\r\n\r\n\r\n\r\n\r\n");
	puts(L"                         ");
	puts(L"2017-10-22 版  ");

	ST->ConOut->SetAttribute(ST->ConOut,
				 EFI_MAGENTA | EFI_BACKGROUND_LIGHTGRAY);
	puts(L"henyapente ");

	ST->ConOut->SetAttribute(ST->ConOut,
				 EFI_BLUE | EFI_BACKGROUND_LIGHTGRAY);
	puts(L"発 行\r\n");

	while (TRUE);
}
