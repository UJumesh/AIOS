const express = require("express");
const { exec } = require("child_process");

const app = express();

const PORT = 3000;

app.get("/", (req, res) => {
    res.send("AIOS Backend is Running");
});

app.get("/api/status", (req, res) => {
    res.json({
        system: "AIOS",
        status: "running"
    });
});

app.get("/api/processes", (req, res) => {

    exec("ps -eo pid,comm,%cpu,%mem --no-headers", (error, stdout) => {

        if (error) {
            return res.status(500).json({
                error: "Unable to get process information"
            });
        }

        const lines = stdout.trim().split("\n");

        const processes = lines.map(line => {

            const parts = line.trim().split(/\s+/);

            return {
                pid: parts[0],
                name: parts[1],
                cpu: parts[2],
                memory: parts[3]
            };
        });

        res.json(processes);
    });
});

app.listen(PORT, () => {
    console.log(`AIOS Backend running on port ${PORT}`);
});