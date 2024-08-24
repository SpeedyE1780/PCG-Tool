import styles from "../../styles/Home.module.css";
import Vector3 from "./vector3";

export default function GenerationParameters(props) {
  return (
    <div className={styles.viewerParams}>
      <label>Node Count</label>
      <input
        placeholder="100"
        onChange={(event) => (props.config.count = event.target.value)}
      ></input>
      <label>Node Size</label>
      <input
        placeholder="1"
        onChange={(event) => (props.config.size = event.target.value)}
      ></input>

      <label>Start Position</label>
      <Vector3
        onXChange={(event) => (props.config.xPosition = event.target.value)}
        onYChange={(event) => (props.config.yPosition = event.target.value)}
        onZChange={(event) => (props.config.zPosition = event.target.value)}
      ></Vector3>

      {!props.hideAxis && <label>Generation Axis</label>}
      {!props.hideAxis && (
        <input
          type="number"
          placeholder="Axis"
          onChange={(event) => {
            props.config.axis = event.target.valueAsNumber;
          }}
        ></input>
      )}
    </div>
  );
}
