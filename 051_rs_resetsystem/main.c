#include "efi.h"
#include "common.h"

void efi_main(void *ImageHandle __attribute__ ((unused)),
	      struct EFI_SYSTEM_TABLE *SystemTable)
{
	efi_init(SystemTable);
	ST->ConOut->ClearScreen(ST->ConOut);

	/* キー入力待ち */
	puts(L"何かキーを押すとシャットダウンします。。。\r\n");
	getc();

	/* シャットダウン */
	ST->RuntimeServices->ResetSystem(EfiResetShutdown, EFI_SUCCESS, 0,
					 NULL);

	while (TRUE);
}
