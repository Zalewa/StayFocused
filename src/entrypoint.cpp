#include "main.h"

#ifdef _MSC_VER
#ifdef NDEBUG
#define USE_WINMAIN_AS_ENTRY_POINT
#endif
#endif

#ifdef USE_WINMAIN_AS_ENTRY_POINT
#include <windows.h>
#include <QStringList>
QStringList getCommandLineArgs()
{
    QString cmdLine = QString::fromUtf16((const ushort*)GetCommandLineW());
    if (cmdLine.isEmpty())
    {
        // CommandLineToArgvW() returns path to current executable
        // if lpCmdLine argument is an empty string. We don't want that
        // here.
        return QStringList();
    }
    int numArgs = 0;
    LPCWSTR winapiCmdLine = (LPCWSTR)cmdLine.utf16();
    LPWSTR* winapiTokens = CommandLineToArgvW(winapiCmdLine, &numArgs);

    if (winapiTokens == NULL)
    {
        return QStringList();
    }

    QStringList result;
    for (int i = 0; i < numArgs; ++i)
    {
        // Conversion to "ushort*" seems to work for LPWSTR.
        result << QString::fromUtf16((const ushort*)winapiTokens[i]);
    }
    LocalFree(winapiTokens);
    return result;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int nCmdShow)
{
    int argc = 0;
    char** argv = NULL;

    QStringList commandLine = getCommandLineArgs();

    // At least one is ensured to be here.
    argc = commandLine.size();
    argv = new char*[argc];

    for (int i = 0; i < commandLine.size(); ++i)
    {
        const QString& parameter = commandLine[i];
        argv[i] = new char[parameter.toUtf8().size() + 1];
        strcpy(argv[i], parameter.toUtf8().constData());
    }

    Main* pMain = new Main(argc, argv);
    int returnValue = pMain->run();

    // Cleans up after the program.
    delete pMain;

    // On the other hand we could just ignore the fact that this array is left
    // hanging in the memory because Windows will clean it up for us...
    for (int i = 0; i < argc; ++i)
    {
        delete [] argv[i];
    }
    delete [] argv;

    return returnValue;
}
#else
int main(int argc, char* argv[])
{
    Main* pMain = new Main(argc, argv);
    int returnValue = pMain->run();

    // Cleans up after the program.
    delete pMain;

    return returnValue;
}
#endif
