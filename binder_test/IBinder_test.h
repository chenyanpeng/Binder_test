#ifndef _IBINDER_TEST_
#define _IBINDER_TEST_

#include <utils/Vector.h>
#include <utils/String8.h>
#include <utils/String16.h>
#include <utils/Log.h>
#include <utils/SystemClock.h>

#include <binder/IInterface.h>
#include <binder/IPermissionController.h>
#include <binder/IPCThreadState.h>
#include <binder/Parcel.h>

#include <private/binder/Static.h>

#include <unistd.h>


namespace android{
	enum 
	{
		SHOW = IBinder::FIRST_CALL_TRANSACTION,
		NAME,
		TOTAL,
	};
	class IBinder_test : public IInterface
	{
	public:
		DECLARE_META_INTERFACE(Binder_test);
		virtual void show() const = 0;
		virtual String8 getName(String8 str1,String8 str2) const = 0;
		virtual int getTotal(int num1,int num2) const = 0;	
	};


	class BpBinder_test : public BpInterface<IBinder_test>
	{
	public:
	    BpBinder_test(const sp<IBinder>& impl)
	        : BpInterface<IBinder_test>(impl)
	    {
	    }

		virtual void show() const
	    {
	    	Parcel data, reply;
        	data.writeInterfaceToken(IBinder_test::getInterfaceDescriptor());
      		remote()->transact(SHOW, data, &reply);
	    }

	    virtual String8 getName(String8 str1,String8 str2) const
	    {
	    	Parcel data, reply;
        	data.writeInterfaceToken(IBinder_test::getInterfaceDescriptor());
        	data.writeString8(str1);
        	data.writeString8(str2);
        	remote()->transact(NAME, data, &reply);
        	return reply.readString8();
	    }

	    virtual int getTotal(int num1,int num2) const
	    {
	    	Parcel data, reply;
        	data.writeInterfaceToken(IBinder_test::getInterfaceDescriptor());
        	data.writeInt32(num1);
        	data.writeInt32(num2);
        	remote()->transact(TOTAL, data, &reply);
        	return reply.readInt32();	    	
	    }
	};

	IMPLEMENT_META_INTERFACE(Binder_test, "android.os.IBinder_test");
}
#endif