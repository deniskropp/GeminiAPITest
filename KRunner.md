To integrate your QML application with KRunner, you can create a KRunner plugin using the KDE framework. Here's a step-by-step guide:

### 1. **Set Up a KRunner Plugin Project**
   - **Language**: Use C++ (KRunner plugins are implemented in C++).
   - **Dependencies**: Install `krunner`, `plasma-framework`, and Qt development packages.
   - **Project Structure**:
     ```
     MyQMLRunner/
     ├── CMakeLists.txt
     ├── myqmlrunner.h
     └── myqmlrunner.cpp
     ```

### 2. **Implement the Plugin**
   - **Header File (`myqmlrunner.h`)**:
     ```cpp
     #include <KRunner/AbstractRunner>

     class MyQMLRunner : public Plasma::AbstractRunner {
         Q_OBJECT

     public:
         MyQMLRunner(QObject *parent, const KPluginMetaData &metaData);
         void match(Plasma::RunnerContext &context) override;
         void run(const Plasma::RunnerContext &context, const Plasma::QueryMatch &match) override;
     };
     ```

   - **Source File (`myqmlrunner.cpp`)**:
     ```cpp
     #include "myqmlrunner.h"
     #include <QDebug>

     MyQMLRunner::MyQMLRunner(QObject *parent, const KPluginMetaData &metaData)
         : AbstractRunner(parent, metaData) {
         setPriority(HighestPriority);
     }

     void MyQMLRunner::match(Plasma::RunnerContext &context) {
         const QString query = context.query();
         // Query your QML application here (e.g., via DBus or shared files)
         // Add matches to `context` using addMatch()
     }

     void MyQMLRunner::run(const Plasma::RunnerContext &context, const Plasma::QueryMatch &match) {
         Q_UNUSED(context)
         // Execute actions in your QML app (e.g., open a file, trigger a function)
     }
     ```

### 3. **Communicate with Your QML Application**
   - **Use DBus**:
     - Expose a DBus interface in your QML app using `QtDBus`.
     - In the plugin, call DBus methods to fetch data or trigger actions.
   - **Example DBus Call**:
     ```cpp
     QDBusInterface interface("com.example.MyQMLApp", "/", "", QDBusConnection::sessionBus());
     QDBusReply<QStringList> reply = interface.call("getRecentTasks");
     ```

### 4. **Build and Install the Plugin**
   - **CMakeLists.txt**:
     ```cmake
     find_package(KF5Runner REQUIRED)
     add_library(myqmlrunner MODULE myqmlrunner.cpp)
     target_link_libraries(myqmlrunner KF5::Runner)
     install(TARGETS myqmlrunner DESTINATION ${KDE_INSTALL_PLUGINDIR}/krunner)
     ```
   - Build and install:
     ```
     mkdir build && cd build
     cmake .. && make
     sudo make install
     ```

### 5. **Register the Plugin**
   - Create a metadata file `myqmlrunner.desktop`:
     ```ini
     [Desktop Entry]
     Type=Service
     X-KDE-ServiceTypes=KRunner/Plugin
     X-KDE-Library=myqmlrunner
     X-KDE-PluginInfo-Name=myqmlrunner
     X-KDE-PluginInfo-Author=YourName
     X-KDE-PluginInfo-License=GPL
     ```

### 6. **Test the Integration**
   - Restart KRunner: `kquitapp5 krunner && krunner`.
   - Trigger KRunner (Alt+F2) and test your plugin.

### Key Customization Points:
- **Match Logic**: In `match()`, fetch data from your QML app and populate matches (e.g., recent tasks, open documents).
- **Actions**: Use `run()` to trigger actions like opening files or executing commands in your app.
- **DBus Integration**: Ensure your QML app exposes necessary APIs for the plugin to interact with.

### Troubleshooting:
- Check logs with `journalctl --user -u plasma-krunner`.
- Verify DBus connectivity with `qdbusviewer`.

By following these steps, your QML application will integrate seamlessly with KRunner, allowing users to query and interact with it directly from the desktop environment.