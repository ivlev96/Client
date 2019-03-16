HEADERS += \
	$$files($$PWD/*.h) \
	$$files($$PWD/authorization/*.h) \
	$$files($$PWD/common/*.h) \
	$$files($$PWD/controllers/*.h) \
	$$files($$PWD/models/*.h) \
	$$files($$PWD/network/*.h) \
        $$files($$PWD/widgets/mainwindow/*.h) \

SOURCES += \
	$$files($$PWD/*.cpp) \
	$$files($$PWD/authorization/*.cpp) \
	$$files($$PWD/common/*.cpp) \
	$$files($$PWD/controllers/*.cpp) \
	$$files($$PWD/models/*.cpp) \
	$$files($$PWD/network/*.cpp) \
        $$files($$PWD/widgets/mainwindow/*.cpp) \
	
FORMS += \
        $$files($$PWD/widgets/mainwindow/*.ui) \

RESOURCES += \
    Resources/client.qrc
	
PRECOMPILED_HEADER = stdafx.h
