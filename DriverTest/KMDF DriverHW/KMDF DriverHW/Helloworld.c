#pragma warning (disable : 4100)
#include "Helloworld.h"
#include "messages.h"

NTSTATUS DriverEntry(PDRIVER_OBJECT pDriverObject, PUNICODE_STRING pRegistryPath) {

	pDriverObject->DriverUnload = UnloadDriver;
	DbgPrintEx(0, 0, "Message!");
	DebugMessage("Hello World!");
	return STATUS_SUCCESS;
}

NTSTATUS UnloadDriver(PDRIVER_OBJECT pDriverObject) {
	DebugMessage("Goodbye!");
	return STATUS_SUCCESS;
}