import * as pc from "playcanvas";
import { SpawnWFCLevel } from "../components/playcanvas/spawnLevelNode";
import Viewer from "../components/playcanvas/viewer";
import GenerationParameters from "../components/levelGeneration/generationParameters";
import PCGMain from "../components/pcgMain";

export default function WaveFunctionCollapse() {
  let params = {};
  let expansion = 0;

  async function generateLevel() {
    const generationParameters = {
      nodeCount: params.count,
      nodeSize: params.size,
      startPosition: {
        x: params.xPosition,
        y: params.yPosition,
        z: params.zPosition,
      },
      axes: params.axis,
      expansionMode: expansion,
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
          SpawnWFCLevel(body, generationParameters.nodeSize);
        })
        .catch((err) => console.log(err));
    } else {
      alert("Error in result");
    }
  }

  return (
    <PCGMain>
      <Viewer>
        <h1>Wave Function Collapse Generation</h1>
        <GenerationParameters config={params}></GenerationParameters>
        <label>Expansion Mode</label>
        <select onChange={(event) => (expansion = event.target.selectedIndex)}>
          <option value="BFS">Breadth First Search</option>
          <option value="DFS">Depth First Search</option>
        </select>
        <button onClick={generateLevel}>Generate</button>
      </Viewer>
    </PCGMain>
  );
}
