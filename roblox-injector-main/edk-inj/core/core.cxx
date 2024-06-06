#include <core/core.hxx>

using namespace std;

//  @TODO: Improve the method.


/*  Made by discord @uskult & github @latviankult  */

/*  Looking for good & undetected injection method? Add me on discord.  */

auto main ( ) -> int {

    SetConsoleTitleA("discord.gg/external");

	if (authenticated)
	std::cout << "Welcome Back (...)" << std::endl;

	/* -- Debug Privilege -- */

	check_return(enable_privilege("SeDebugPrivilege"), "Can't enable debug privilege");

    /* -- Errors -- */

	check_return(std::filesystem::exists("sdk.dll"), "Failed to find cheat DLL");

	char file_path[MAX_PATH];

    check_return(GetFullPathNameA("sdk.dll", sizeof(file_path), file_path, nullptr), "Failed to get Path");

    const auto process_pid = wait_for_object([]() {
       auto process_id = 0ul;
       
       // @TODO: Fix anti-paste to make it work. Kisses from Kult.

       // @TODO: Add Process Check.

       return process_id;
        });

    auto process_id = 0ul;

    const auto process_handle = unique_handle{ OpenProcess(PROCESS_ALL_ACCESS, false, process_pid), &CloseHandle };

    check_return(process_handle, "Can't open handle");

    const auto allocated_buffer =
        VirtualAllocEx(process_handle.get(), nullptr, strlen(file_path) + 1, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

    check_return(allocated_buffer, "Can't allocate buffer");
    check_return(WriteProcessMemory(process_handle.get(), allocated_buffer, file_path, strlen(file_path) + 1, nullptr),
        "Can't copy buffer");

    /* -- Injection -- */

    const auto thread_handle = unique_handle{
        CreateRemoteThread(process_handle.get(), nullptr, 0, (LPTHREAD_START_ROUTINE)LoadLibraryA, allocated_buffer, 0, nullptr),
        &CloseHandle };

    check_return(thread_handle, "Failed to start thread");

    WaitForSingleObject(thread_handle.get(), INFINITE);
    VirtualFreeEx(process_handle.get(), allocated_buffer, 0, MEM_RELEASE);

    /* -- End -- */

    return EXIT_SUCCESS;

}		