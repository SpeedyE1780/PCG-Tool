import Game from "../components/playcanvas/game";

export default function SimpleGeneration() {
  let count = 0;
  let size = 1;
  let x = 0;
  let y = 0;
  let z = 0;
  let axis = 0;

  return (
    <div style={{ display: "flex" }}>
      <div>
        <h1>Simple Generation</h1>
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
          onChange={(event) => (x = event.target.value)}
        ></input>
        <input
          placeholder="Start Position Y"
          onChange={(event) => (y = event.target.value)}
        ></input>
        <input
          placeholder="Start Position Z"
          onChange={(event) => (z = event.target.value)}
        ></input>
        <input
          placeholder="Axis"
          onChange={(event) => (axis = event.target.value)}
        ></input>
        <button>Generate</button>
      </div>
      <Game></Game>
    </div>
  );
}
