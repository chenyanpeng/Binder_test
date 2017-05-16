
#include "IBinder_test.h"

using namespace android;

int main(void)
{
	sp<ProcessState> proc(ProcessState::self());
	sp<IServiceManager> sm = defaultServiceManager();
	sp<IBinder> binder = sm->getService(String16("binder_testservice"));
	sp<IBinder_test> cl = interface_cast<IBinder_test>(binder);
	fprintf(stderr, "%s\n",(cl->getName(String8("hello"),String8("world"))).string());
	fprintf(stderr, "%d\n",cl->getTotal(12,13));
}