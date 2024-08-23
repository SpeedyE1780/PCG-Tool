import { useState } from "react";
import PCGMain from "../components/pcgMain";
import NodeList from "../components/sequence/nodeList";
import { PCGRequest } from "../components/pcgRequest";
import styles from "../styles/Home.module.css";

let startNodeID = 0;
let sequence = "";
let generatedSequenceLength = 1;
let nodeCount = 0;

export default function CyclicSequenceGeneration() {
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

      sequenceLength: nodeCount,
    };

    PCGRequest(
      "https://localhost:7060/sequence/generatecyclicsequence",
      sequenceParameters,
      (body) => {
        console.log(sequenceParameters.sequenceLength);
        let sequenceArray = JSON.parse(body);
        sequence = "";
        generatedSequenceLength = sequenceArray.length + 1;
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
        <div>
          <label>Sequence Length</label>
          <input
            onChange={(event) => {
              nodeCount = Number(event.target.value);
            }}
          ></input>
        </div>
        <button onClick={generateSequence}>Generate</button>
        <textarea
          className={styles.viewerResponseArea}
          readOnly={true}
          value={sequence}
          rows={generatedSequenceLength}
        ></textarea>
      </div>
    </PCGMain>
  );
}
