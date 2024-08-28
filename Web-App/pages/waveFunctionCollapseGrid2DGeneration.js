import { Planes, SpawnWFCGrid } from "../components/playcanvas/spawnWFCLevel";
import Viewer from "../components/playcanvas/viewer";
import GridConfiguration from "../components/levelGeneration/gridConfiguration";
import PCGMain from "../components/pcgMain";
import { useState } from "react";
import { PCGRequest } from "../components/pcgRequest";

let gridConfig = {};
let gridPlane = Planes[0];

export default function WaveFunctionCollapseGrid2DGeneration() {
  let [generatedJSON, setGeneratedJSON] = useState("");

  function generateGrid() {
    const gridParameters = {
      width: gridConfig.width,
      height: gridConfig.height,
      plane: gridPlane,
    };

    PCGRequest(
      "https://localhost:7060/levelgeneration/wavefunctioncollapsegeneration/grid2d",
      gridParameters,
      (json) => {
        setGeneratedJSON(json);
        SpawnWFCGrid(JSON.parse(json), gridPlane);
      }
    );
  }

  return (
    <PCGMain>
      <Viewer responseJSON={generatedJSON}>
        <h1>Wave Function Collapse Grid 2D Generation</h1>
        <GridConfiguration config={gridConfig}></GridConfiguration>
        <label>Grid Plane</label>
        <select
          onChange={(event) => {
            gridPlane = Planes[event.target.selectedIndex];
          }}
        >
          <option value="XY">XY</option>
          <option value="XZ">XZ</option>
          <option value="YZ">YZ</option>
        </select>
        <button onClick={generateGrid}>Generate</button>
      </Viewer>
    </PCGMain>
  );
}
