import styles from "../../styles/Home.module.css";

export default function GridConfiguration(props) {
  if (props.is3D) {
    return (
      <div className={styles.viewerParams}>
        <labe>Grid Width</labe>
        <input
          placeholder="10"
          onChange={(event) => (props.config.width = event.target.value)}
        ></input>
        <label>Grid Height</label>
        <input
          placeholder="10"
          onChange={(event) => (props.config.height = event.target.value)}
        ></input>
        <label>Grid Depth</label>
        <input
          placeholder="10"
          onChange={(event) => (props.config.depth = event.target.value)}
        ></input>
      </div>
    );
  }

  return (
    <div className={styles.viewerParams}>
      <labe>Grid Width</labe>
      <input
        placeholder="10"
        onChange={(event) => (props.config.width = event.target.value)}
      ></input>
      <label>Grid Height</label>
      <input
        placeholder="10"
        onChange={(event) => (props.config.height = event.target.value)}
      ></input>
    </div>
  );
}
