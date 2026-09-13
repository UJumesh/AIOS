import { useEffect, useState } from "react";
import "./App.css";

function App() {

  const [processes, setProcesses] = useState([]);
  const [system, setSystem] = useState({
    cpu: "--",
    memory: "--"
  });

  useEffect(() => {

    fetch("/api/processes")
      .then(response => response.json())
      .then(data => {
        setProcesses(data);
      })
      .catch(error => {
        console.log("Process Error:", error);
      });

    fetch("/api/system")
      .then(response => response.json())
      .then(data => {
        setSystem(data);
      })
      .catch(error => {
        console.log("System Error:", error);
      });

  }, []);

  return (
    <div className="dashboard">

      <h1 className="title">AIOS Dashboard</h1>

      <p className="subtitle">
        AI-Assisted Operating System Management System
      </p>

      <div className="cards">

        <div className="card">
          <h3>CPU Usage</h3>
          <p>{system.cpu} %</p>
        </div>

        <div className="card">
          <h3>Memory Usage</h3>
          <p>{system.memory} %</p>
        </div>

        <div className="card">
          <h3>Processes</h3>
          <p>{processes.length}</p>
        </div>

        <div className="card">
          <h3>System Status</h3>
          <p>Online</p>
        </div>

      </div>

      <div className="section">

        <h2>Running Processes</h2>

        <table>

          <thead>
            <tr>
              <th>PID</th>
              <th>Name</th>
              <th>CPU %</th>
              <th>Memory %</th>
            </tr>
          </thead>

          <tbody>

            {processes.map((process) => (
              <tr key={process.pid}>
                <td>{process.pid}</td>
                <td>{process.name}</td>
                <td>{process.cpu}</td>
                <td>{process.memory}</td>
              </tr>
            ))}

          </tbody>

        </table>

      </div>

    </div>
  );
}

export default App;