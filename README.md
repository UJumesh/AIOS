# AIOS — OS Resource Management Experiments

An educational project exploring operating-system algorithms and monitoring, using C, Express and React.

## Components
- `cpu_scheduler/`: FCFS, SJF, priority, and round-robin algorithms with Gantt charts and scheduling metrics
- `memory_manager/`: best-fit and worst-fit allocation examples
- `process_manager/`, `multithreading/`: C exercises
- `backend/`: Express status and Linux process/system metrics API
- `frontend/`: React/Vite dashboard

## Run locally
Backend (requires Node.js and Linux `ps`, `free`, `top`):

```bash
cd backend
npm install
node server.js
```

Frontend in a separate terminal:

```bash
cd frontend
npm install
npm run dev
```

C scheduler:

```bash
gcc cpu_scheduler/main.c -o scheduler
./scheduler
```

## API and safety
Backend uses port 3000 and exposes `/`, `/api/status`, `/api/processes`, and `/api/system`. Its process information routes lack authentication and permit broad CORS. Use on trusted machines only, and do not expose to the internet without hardening. End-to-end functionality has not been independently verified.
