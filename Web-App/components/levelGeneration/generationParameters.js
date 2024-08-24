import styles from "../../styles/Home.module.css";

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
      <div className={styles.vector3Row}>
        <label className={styles.rightAlignLabel}>X</label>
        <label className={styles.rightAlignLabel}>Y</label>
        <label className={styles.rightAlignLabel}>Z</label>
      </div>
      <div className={styles.vector3Row}>
        <input
          className={styles.rightAlignLabel}
          placeholder="0"
          onChange={(event) => (props.config.xPosition = event.target.value)}
        ></input>
        <input
          className={styles.rightAlignLabel}
          placeholder="0"
          onChange={(event) => (props.config.yPosition = event.target.value)}
        ></input>
        <input
          className={styles.rightAlignLabel}
          placeholder="0"
          onChange={(event) => (props.config.zPosition = event.target.value)}
        ></input>
      </div>

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
