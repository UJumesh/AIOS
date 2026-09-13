const express = require("express");
const cors = require("cors");
const { exec } = require("child_process");

const app = express();

const PORT = 3000;

app.use(cors());

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

app.get("/api/system", (req, res) => {

    exec("free -m", (error, stdout) => {

        if (error) {
            return res.status(500).json({
                error: "Unable to get memory information"
            });
        }

        const lines = stdout.trim().split("\n");
        const memory = lines[1].trim().split(/\s+/);

        const total = Number(memory[1]);
        const used = Number(memory[2]);

        const memoryUsage = ((used / total) * 100).toFixed(1);

        exec("top -bn1 | grep 'Cpu(s)'", (cpuError, cpuOutput) => {

            if (cpuError) {
                return res.status(500).json({
                    error: "Unable to get CPU information"
                });
            }

            const match = cpuOutput.match(/(\d+\.\d+)\s*id/);

            let cpuUsage = 0;

            if (match) {
                cpuUsage = (100 - Number(match[1])).toFixed(1);
            }

            res.json({
                cpu: cpuUsage,
                memory: memoryUsage
            });
        });
    });
});

app.listen(PORT, () => {
    console.log(`AIOS Backend running on port ${PORT}`);
});