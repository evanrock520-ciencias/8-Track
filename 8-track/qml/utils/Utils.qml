pragma Singleton
import QtQuick

QtObject {
    function formatTime(ms) {
        const seconds = Math.floor(ms / 1000);
        return Math.floor(seconds / 60) + ":" + String(seconds % 60).padStart(2, "0");
    }
}
