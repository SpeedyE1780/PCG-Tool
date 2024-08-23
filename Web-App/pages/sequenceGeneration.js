import { useState } from "react";
import PCGMain from "../components/pcgMain";
import NodeList from "../components/sequence/nodeList";
import { PCGRequest } from "../components/pcgRequest";
import styles from "../styles/Home.module.css";

let startNodeID = 0;
let sequence = "";
let sequenceLength = 1;

export default function SequenceGeneration() {
  let [nodesList, setList] = useState([]);

  function refreshState() {
    setList(nodesList.map((element) => element));
  }

  function addNode() {
    nodesList.push({ id: nodesList.length, name: "", nextNodes: [] });
    refreshState();
  }

  function generateSequence() {
    const sequenceParameters = {
      start: {
        id: startNodeID,
        nextNodes: nodesList[startNodeID].nextNodes,
      },

      nodes: nodesList.map((node) => ({
        id: node.id,
        nextNodes: node.nextNodes,
      })),
    };

    PCGRequest(
      "https://localhost:7060/sequence/generate",
      sequenceParameters,
      (body) => {
        let sequenceArray = JSON.parse(body);
        sequence = "";
        sequenceLength = sequenceArray.length + 1;
        sequenceArray.forEach((index) => {
          sequence += `${nodesList[index].name}\n`;
        });
        refreshState();
      }
    );
  }

  return (
    <PCGMain>
      <div className={styles.sequenceParams}>
        <button onClick={addNode}>Add Node</button>
        <NodeList nodes={nodesList}></NodeList>
        <div>
          <label>Start Node ID</label>
          <input
            onChange={(event) => (startNodeID = event.target.value)}
          ></input>
        </div>
        <button onClick={generateSequence}>Generate</button>
        <textarea
          className={styles.viewerResponseArea}
          readOnly={true}
          value={sequence}
          rows={sequenceLength}
        ></textarea>
      </div>
    </PCGMain>
  );
}
