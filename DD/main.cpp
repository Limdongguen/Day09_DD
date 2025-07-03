#include "gmock/gmock.h"
#include "device_driver.h"
#include "flash_memory_device.h"
#include <string>

using std::string;
using namespace testing;


class MockFlashMemoryDevice : public FlashMemoryDevice
{
public:
	MOCK_METHOD(unsigned char, read, (long address), (override));
	MOCK_METHOD(void, write, (long address, unsigned char data), (override));
};

class DeviceDriverFixture : public Test {
public:
	MockFlashMemoryDevice mockFlashMemoryDevice;
	DeviceDriver driver{ &mockFlashMemoryDevice };
};

TEST_F(DeviceDriverFixture, ReadFromHW) {
	// TODO : replace hardware with a Test Double
	EXPECT_CALL(mockFlashMemoryDevice, read((int)0xFF)).Times(5).WillRepeatedly(Return('c'));
	char data = driver.read(0xFF);
	EXPECT_EQ('c', data);
}

TEST_F(DeviceDriverFixture, ReadErrorFromHW) {
	// TODO : replace hardware with a Test Double
	EXPECT_CALL(mockFlashMemoryDevice, read((int)0xFF)).WillOnce(Return('c')).WillRepeatedly(Return('d'));
	EXPECT_THROW(driver.read((int)0xFF), std::exception);
}

TEST_F(DeviceDriverFixture, WriteFromHW) {
	// TODO : replace hardware with a Test Double
	EXPECT_CALL(mockFlashMemoryDevice, read(0xA)).WillRepeatedly(Return((int)0xFF));
	driver.write((int)0xA, (int)0x31);
}

TEST_F(DeviceDriverFixture, WriteErrorFromHW) {
	// TODO : replace hardware with a Test Double
	EXPECT_CALL(mockFlashMemoryDevice, read(0xA)).WillRepeatedly(Return((int)0xF));
	EXPECT_THROW(driver.write((int)0xA, (int)0x31), std::exception);
}

int main() {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}