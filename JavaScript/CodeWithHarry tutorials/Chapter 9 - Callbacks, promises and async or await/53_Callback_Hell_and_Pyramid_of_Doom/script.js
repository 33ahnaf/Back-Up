function sendEmergencyMessageToCEO() {
    void(0);
}

function loadScript(src, callback) {
    let script = document.createElement("script");
    script.src = src;
    script.onload = function() {
        callback(null, src);
    }
    script.onerror = function() {
        callback(new Error("Script got some error!"));
    }
    document.body.appendChild(script);
}

loadScript("https://cdn.jsdelivr.net/npm/bootstrap@5.2.1/dist/js/bootstrap.bundle.min.js", function load_alert(error, src) {
    if (error) {
        console.log(error);
        sendEmergencyMessageToCEO();
        return;
    }
    console.log("Loaded SRC: " + src);
    loadScript("https://cdn.jsdelivr.net/npm/bootstrap@5.2.1/dist/js/bootstrap2.bundle.min.js", function load_alert(error, src) {
        if (error) {
            console.log(error);
            sendEmergencyMessageToCEO();
            return;
        }
        console.log("Loaded SRC: " + src);
        loadScript("https://cdn.jsdelivr.net/npm/bootstrap@5.2.1/dist/js/bootstrap3.bundle.min.js", function load_alert(error, src) {
            if (error) {
                console.log(error);
                sendEmergencyMessageToCEO();
                return;
            }
            console.log("Loaded SRC: " + src);
            loadScript("https://cdn.jsdelivr.net/npm/bootstrap@5.2.1/dist/js/bootstrap4.bundle.min.js", function load_alert(error, src) {
                if (error) {
                    console.log(error);
                    sendEmergencyMessageToCEO();
                    return;
                }
                console.log("Loaded SRC: " + src);
                loadScript("https://cdn.jsdelivr.net/npm/bootstrap@5.2.1/dist/js/bootstrap5.bundle.min.js", function load_alert(error, src) {
                    if (error) {
                        console.log(error);
                        sendEmergencyMessageToCEO();
                        return;
                    }
                    console.log("Loaded SRC: " + src);
                    loadScript("https://cdn.jsdelivr.net/npm/bootstrap@5.2.1/dist/js/bootstrap6.bundle.min.js", function load_alert(error, src) {
                        if (error) {
                            console.log(error);
                            sendEmergencyMessageToCEO();
                            return;
                        }
                        console.log("Loaded SRC: " + src);
                        loadScript("https://cdn.jsdelivr.net/npm/bootstrap@5.2.1/dist/js/bootstrap7.bundle.min.js", function load_alert(error, src) {
                            if (error) {
                                console.log(error);
                                sendEmergencyMessageToCEO();
                                return;
                            }
                            console.log("Loaded SRC: " + src);
                            loadScript("https://cdn.jsdelivr.net/npm/bootstrap@5.2.1/dist/js/bootstrap8.bundle.min.js", function load_alert(error, src) {
                                if (error) {
                                    console.log(error);
                                    sendEmergencyMessageToCEO();
                                    return;
                                }
                                console.log("Loaded SRC: " + src);
                                loadScript("https://cdn.jsdelivr.net/npm/bootstrap@5.2.1/dist/js/bootstrap9.bundle.min.js", function load_alert(error, src) {
                                    if (error) {
                                        console.log(error);
                                        sendEmergencyMessageToCEO();
                                        return;
                                    }
                                    console.log("Loaded SRC: " + src);
                                })
                            })
                        })
                    })
                })
            })
        })
    })
});