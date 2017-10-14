#include "efi.h"
#include "common.h"

void efi_main(void *ImageHandle, struct EFI_SYSTEM_TABLE *SystemTable)
{
	struct EFI_LOADED_IMAGE_PROTOCOL *lip;
	struct EFI_DEVICE_PATH_PROTOCOL *dev_path;
	struct EFI_DEVICE_PATH_PROTOCOL *dev_node;
	struct EFI_DEVICE_PATH_PROTOCOL *dev_path_merged;
	unsigned long long status;

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

	/* "test.efi"のデバイスノードを作成 */
	dev_node = DPFTP->ConvertTextToDeviceNode(L"test.efi");

	/* dev_pathとdev_nodeを連結 */
	dev_path_merged = DPUP->AppendDeviceNode(dev_path, dev_node);

	/* dev_path_mergedをテキストへ変換し表示 */
	puts(L"dev_path_merged: ");
	puts(DPTTP->ConvertDevicePathToText(dev_path_merged, FALSE, FALSE));
	puts(L"\r\n");

	while (TRUE);
}
