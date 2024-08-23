import * as pc from "playcanvas";
import Game from "../components/playcanvas/game";
import { SpawnWFCGrid3D } from "../components/playcanvas/spawnLevelNode";
import Viewer from "../components/playcanvas/viewer";

export default function waveFunctionCollapseGrid3D() {
  let gridWidth = 0;
  let gridHeight = 0;
  let gridDepth = 0;

  async function generateGrid() {
    let gridParameters = {
      width: gridWidth,
      height: gridHeight,
      depth: gridDepth,
    };

    console.log(gridParameters);

    pc.app.fire("DestroyNode");

    var request = {
      method: "POST",
      headers: {
        "content-type": "application/json",
      },
      body: JSON.stringify(gridParameters),
    };

    const result = await fetch(
      "https://localhost:7060/levelgeneration/wavefunctioncollapsegeneration/grid3d",
      request
    );

    if (result.ok) {
      result
        .json()
        .then((body) => {
          console.log(body);
          SpawnWFCGrid3D(body);
        })
        .catch((err) => console.log(err));
    } else {
      alert("Error in result");
    }
  }

  return (
    <Viewer>
      <div>
        <h1>Wave Function Collapse Grid 3D Generation</h1>
        <input
          placeholder="Grid Width"
          onChange={(event) => (gridWidth = event.target.value)}
        ></input>
        <input
          placeholder="Grid Height"
          onChange={(event) => (gridHeight = event.target.value)}
        ></input>
        <input
          placeholder="Grid Depth"
          onChange={(event) => (gridDepth = event.target.value)}
        ></input>
        <button onClick={generateGrid}>Generate</button>
      </div>
    </Viewer>
  );
}
