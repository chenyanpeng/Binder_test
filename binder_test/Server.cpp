#include "IBinder_test.h"
namespace android{
	class BnBinder_test : public BnInterface<IBinder_test>
	{
	public:
    	virtual status_t onTransact( uint32_t code,
                                    const Parcel& data,
                                    Parcel* reply,
                                    uint32_t flags = 0);
    	void show() const{
    		fprintf(stderr, "%s\n","message from client");
    	}
		
		String8 getName(String8 str1,String8 str2) const{
			return String8("message from binder server");
		}

		int getTotal(int num1,int num2) const{
			return num1 + num2;
		}
	};
	status_t BnBinder_test::onTransact(
    uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags)
	{
	    //printf("ServiceManager received: "); data.print();
	    switch(code) {
	        case SHOW: {
	            CHECK_INTERFACE(IBinder_test, data, reply);
	            show();
	            return NO_ERROR;
	        } break;
	        case NAME: {
	        	CHECK_INTERFACE(IBinder_test, data, reply);
	        	String8 str1 = data.readString8();
	        	String8 str2 = data.readString8();
	        	reply->writeString8(getName(str1,str2));
	        	return NO_ERROR;
	        } break;
	        case TOTAL: {
	        	int num1 = data.readInt32();
	        	int num2 = data.readInt32();
	        	reply->writeInt32(getTotal(num1,num2));
	        	return NO_ERROR;
	        } break;
	        default:
	            return BBinder::onTransact(code, data, reply, flags);
	    }
	}
}

using namespace android;
int main(void)
{
	sp<ProcessState> proc(ProcessState::self());
	sp<IServiceManager> sm = defaultServiceManager();
	sm->addService(String16("binder_testservice"),new BnBinder_test());
	ProcessState::self()->startThreadPool();
	IPCThreadState::self()->joinThreadPool();
}