#include "efi.h"
#include "common.h"

void efi_main(void *ImageHandle __attribute__ ((unused)),
	      struct EFI_SYSTEM_TABLE *SystemTable)
{
	unsigned long long status;
	void *tevent;
	void *wait_list[1];
	unsigned long long idx;

	efi_init(SystemTable);
	ST->ConOut->ClearScreen(ST->ConOut);

	/* タイマーイベントを作成し、teventへ格納 */
	status = ST->BootServices->CreateEvent(EVT_TIMER, 0, NULL, NULL,
					       &tevent);
	assert(status, L"CreateEvent");

	/* WaitForEvent()へ渡す為にイベントリストを作成 */
	wait_list[0] = tevent;

	while (TRUE) {
		/* teventへ1秒のトリガー時間を設定 */
		status = ST->BootServices->SetTimer(tevent, TimerRelative,
						    10000000);
		assert(status, L"SetTimer");

		/* イベント発生を待つ */
		status = ST->BootServices->WaitForEvent(1, wait_list, &idx);
		assert(status, L"WaitForEvent");

		/* 画面へ"wait."を出力 */
		puts(L"wait.");
	}
}
