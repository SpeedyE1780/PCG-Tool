import { SpawnWFCGrid3D } from "../components/playcanvas/spawnWFCLevel";
import Viewer from "../components/playcanvas/viewer";
import GridConfiguration from "../components/levelGeneration/gridConfiguration";
import PCGMain from "../components/pcgMain";
import { PCGRequest } from "../components/pcgRequest";
import { useState } from "react";

let gridConfig = {};

export default function WaveFunctionCollapseGrid3DGeneration() {
  let [generatedJSON, setGeneratedJSON] = useState("");

  async function generateGrid() {
    const gridParameters = {
      width: gridConfig.width,
      height: gridConfig.height,
      depth: gridConfig.depth,
    };

    PCGRequest(
      "https://localhost:7060/levelgeneration/wavefunctioncollapsegeneration/grid3d",
      gridParameters,
      (json) => {
        setGeneratedJSON(json);
        SpawnWFCGrid3D(JSON.parse(json));
      }
    );
  }

  return (
    <PCGMain>
      <Viewer responseJSON={generatedJSON}>
        <h1>Wave Function Collapse Grid 3D Generation</h1>
        <GridConfiguration config={gridConfig} is3D={true}></GridConfiguration>
        <button onClick={generateGrid}>Generate</button>
      </Viewer>
    </PCGMain>
  );
}
