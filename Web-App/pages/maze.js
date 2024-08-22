import * as pc from "playcanvas";
import Game from "../components/playcanvas/game";

export default function Maze() {
  let width = 0;
  let height = 0;
  let selectedAlgorithm = 0;
  async function generateMaze() {
    console.log({
      Width: width,
      Height: height,
      Maze: selectedAlgorithm,
    });

    pc.app.fire("DestroyNode");
  }

  return (
    <div style={{ display: "flex" }}>
      <div>
        <h1>Maze Generation</h1>
        <input
          placeholder="Width"
          onChange={(event) => (width = event.target.value)}
        ></input>
        <input
          placeholder="Height"
          onChange={(event) => (height = event.target.value)}
        ></input>
        <select
          onChange={(event) => (selectedAlgorithm = event.target.selectedIndex)}
        >
          <option value="aldousBroder"></option>
          <option value="wilson"></option>
          <option value="binaryTreeNE"></option>
          <option value="binaryTreeNW"></option>
          <option value="binaryTreeSE"></option>
          <option value="binaryTreeSW"></option>
          <option value="sidewinder"></option>
          <option value="eller"></option>
          <option value="huntAndKill"></option>
          <option value="recursiveBacktracker"></option>
          <option value="recursiveDivision"></option>
          <option value="kruskal"></option>
          <option value="prim"></option>
          <option value="growingTreeOldest"></option>
          <option value="growingTreeMiddle"></option>
          <option value="growingTreeNewest"></option>
          <option value="growingTreeRandom"></option>
          <option value="blobbyDivisionCorridors"></option>
          <option value="blobbyDivisionSmall"></option>
          <option value="blobbyDivisionMedium"></option>
          <option value="blobbyDivisionLarge"></option>
          <option value="blobbyDivisionHuge"></option>
        </select>
        <button onClick={generateMaze}>Generate</button>
      </div>
      <Game></Game>
    </div>
  );
}
