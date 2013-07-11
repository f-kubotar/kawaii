#include "skidarake/process/process_manager.h"

#include "skidarake/process/process.h"
#include "skidarake/process/sequence.h"

namespace skidarake {

shared_ptr<Process> ProcessManager::Attach(const shared_ptr<Process>& process) {
    process_list_.push_back(process);
    return process;
}

void ProcessManager::Dettach(const shared_ptr<Process>& process) {
    for (ProcessList::iterator i = process_list_.begin(); i != process_list_.end();) {
        if ((*i) == process) {
            process_list_.erase(i++);
            break;
        } else {
            ++i;
        }
    }
}

bool ProcessManager::Update(const ii_time delta_time) {
    for (ProcessList::iterator i = process_list_.begin(); i != process_list_.end();) {
        shared_ptr<Process> process = (*i);
            
        if (!process->sleeping()) {
            process->Enter();
            
            if (!process->Update(delta_time)) {
                process->Exit();
                process_list_.erase(i++);
            } else {
                ++i;
            }
        } else {
            ++i;
        }
    }
    return true;
}

}
