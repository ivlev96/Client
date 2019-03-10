HEADERS += \
	$$files($$PWD/*.h) \
	$$files($$PWD/authorization/*.h) \
	$$files($$PWD/common/*.h) \
	$$files($$PWD/controllers/*.h) \
	$$files($$PWD/models/*.h) \
	$$files($$PWD/network/*.h) \
	$$files($$PWD/widgets/authorization/*.h) \
	$$files($$PWD/widgets/lastmessages/*.h) \
	$$files($$PWD/widgets/mainwindow/*.h) \
	$$files($$PWD/widgets/messages/*.h) \
	$$files($$PWD/widgets/registration/*.h) \

SOURCES += \
	$$files($$PWD/*.cpp) \
	$$files($$PWD/authorization/*.cpp) \
	$$files($$PWD/common/*.cpp) \
	$$files($$PWD/controllers/*.cpp) \
	$$files($$PWD/models/*.cpp) \
	$$files($$PWD/network/*.cpp) \
	$$files($$PWD/widgets/authorization/*.cpp) \
	$$files($$PWD/widgets/lastmessages/*.cpp) \
	$$files($$PWD/widgets/mainwindow/*.cpp) \
	$$files($$PWD/widgets/messages/*.cpp) \
	$$files($$PWD/widgets/registration/*.cpp) \
	
FORMS += \
	$$files($$PWD/widgets/authorization/*.ui) \
	$$files($$PWD/widgets/lastmessages/*.ui) \
	$$files($$PWD/widgets/mainwindow/*.ui) \
	$$files($$PWD/widgets/messages/*.ui) \
	$$files($$PWD/widgets/registration/*.ui) \

RESOURCES += \
    Resources/client.qrc
	
PRECOMPILED_HEADER = stdafx.h
