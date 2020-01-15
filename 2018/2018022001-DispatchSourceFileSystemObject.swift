import Cocoa

class FileObserver: NSObject {

    var dispatchSource: DispatchSourceFileSystemObject

    init(URL: URL) {
        let descriptor = open(URL.path, O_EVTONLY)
        dispatchSource = DispatchSource.makeFileSystemObjectSource(fileDescriptor: descriptor, eventMask: [.write])
        dispatchSource.setEventHandler {
            print("\(URL.path) changes")
        }
        dispatchSource.activate()
        super.init()
    }

    deinit {
        dispatchSource.cancel()
    }
}
