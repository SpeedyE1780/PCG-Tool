import styles from "../../styles/Home.module.css";

export default function GridConfiguration(props) {
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
