#include "efi.h"
#include "common.h"

void efi_main(void *ImageHandle, struct EFI_SYSTEM_TABLE *SystemTable)
{
	struct EFI_LOADED_IMAGE_PROTOCOL *lip;
	struct EFI_LOADED_IMAGE_PROTOCOL *lip_bzimage;
	struct EFI_DEVICE_PATH_PROTOCOL *dev_path;
	struct EFI_DEVICE_PATH_PROTOCOL *dev_node;
	struct EFI_DEVICE_PATH_PROTOCOL *dev_path_merged;
	unsigned long long status;
	void *image;
	unsigned short options[] = L"root=/dev/sdb2 init=/bin/sh rootwait";

	efi_init(SystemTable);
	ST->ConOut->ClearScreen(ST->ConOut);

	/* ImageHandleのEFI_LOADED_IMAGE_PROTOCOL(lip)を取得 */
	status = ST->BootServices->OpenProtocol(
		ImageHandle, &lip_guid, (void **)&lip, ImageHandle, NULL,
		EFI_OPEN_PROTOCOL_GET_PROTOCOL);
	assert(status, L"OpenProtocol(lip)");

	/* lip->DeviceHandleのEFI_DEVICE_PATH_PROTOCOL(dev_path)を取得 */
	status = ST->BootServices->OpenProtocol(
		lip->DeviceHandle, &dpp_guid, (void **)&dev_path, ImageHandle,
		NULL, EFI_OPEN_PROTOCOL_GET_PROTOCOL);
	assert(status, L"OpenProtocol(dpp)");

	/* "bzImage.efi"のデバイスノードを作成 */
	dev_node = DPFTP->ConvertTextToDeviceNode(L"bzImage.efi");

	/* dev_pathとdev_nodeを連結 */
	dev_path_merged = DPUP->AppendDeviceNode(dev_path, dev_node);

	/* dev_path_mergedをテキストへ変換し表示 */
	puts(L"dev_path_merged: ");
	puts(DPTTP->ConvertDevicePathToText(dev_path_merged, FALSE, FALSE));
	puts(L"\r\n");

	/* dev_path_mergedをロード */
	status = ST->BootServices->LoadImage(FALSE, ImageHandle,
					     dev_path_merged, NULL, 0, &image);
	assert(status, L"LoadImage");
	puts(L"LoadImage: Success!\r\n");

	/* カーネル起動オプションを設定 */
	status = ST->BootServices->OpenProtocol(
		image, &lip_guid, (void **)&lip_bzimage, ImageHandle, NULL,
		EFI_OPEN_PROTOCOL_GET_PROTOCOL);
	assert(status, L"OpenProtocol(lip_bzimage)");
	lip_bzimage->LoadOptions = options;
	lip_bzimage->LoadOptionsSize =
		(strlen(options) + 1) * sizeof(unsigned short);

	/* imageの実行を開始する */
	status = ST->BootServices->StartImage(image, NULL, NULL);
	assert(status, L"StartImage");
	puts(L"StartImage: Success!\r\n");

	while (TRUE);
}
