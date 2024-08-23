import * as pc from "playcanvas";
import { SpawnWFCLevel } from "../components/playcanvas/spawnLevelNode";
import Viewer from "../components/playcanvas/viewer";

export default function WaveFunctionCollapse() {
  let count = 0;
  let size = 1;
  let xPosition = 0;
  let yPosition = 0;
  let zPosition = 0;
  let expansion = 0;
  let axis = 0;

  async function generateLevel() {
    const generationParameters = {
      nodeCount: count,
      nodeSize: size,
      startPosition: {
        x: xPosition,
        y: yPosition,
        z: zPosition,
      },
      expansionMode: expansion,
      axes: axis,
    };
    console.log(generationParameters);

    pc.app.fire("DestroyNode");

    var request = {
      method: "POST",
      headers: {
        "content-type": "application/json",
      },
      body: JSON.stringify(generationParameters),
    };

    const result = await fetch(
      "https://localhost:7060/levelgeneration/wavefunctioncollapsegeneration/generate",
      request
    );

    if (result.ok) {
      result
        .json()
        .then((body) => {
          console.log(body);
          SpawnWFCLevel(body, size);
        })
        .catch((err) => console.log(err));
    } else {
      alert("Error in result");
    }
  }

  return (
    <Viewer>
      <h1>Wave Function Collapse Generation</h1>
      <input
        placeholder="Node Count"
        onChange={(event) => (count = event.target.value)}
      ></input>
      <input
        placeholder="Node Size"
        onChange={(event) => (size = event.target.value)}
      ></input>
      <input
        placeholder="Start Position X"
        onChange={(event) => (xPosition = event.target.value)}
      ></input>
      <input
        placeholder="Start Position Y"
        onChange={(event) => (yPosition = event.target.value)}
      ></input>
      <input
        placeholder="Start Position Z"
        onChange={(event) => (zPosition = event.target.value)}
      ></input>
      <input
        type="number"
        placeholder="Axis"
        onChange={(event) => {
          axis = event.target.valueAsNumber;
        }}
      ></input>
      <select onChange={(event) => (expansion = event.target.selectedIndex)}>
        <option value="BFS"></option>
        <option value="DFS"></option>
      </select>
      <button onClick={generateLevel}>Generate</button>
    </Viewer>
  );
}
