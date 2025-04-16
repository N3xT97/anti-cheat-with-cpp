#include "runtime_factory.h"
#include "runtime_manager.h"
#include "launcher.h"

using namespace std;

RuntimeManager build_runtime_manager(std::string& path)
{
    unique_ptr<WindowsProcessLauncher> launcher = make_unique<WindowsProcessLauncher>();
    return RuntimeManager(move(launcher), path);
}
