import styles from "../../styles/Home.module.css";

export default function Vector3(props) {
  return (
    <div>
      <div className={styles.vector3Row}>
        <label className={styles.rightAlignLabel}>X</label>
        <label className={styles.rightAlignLabel}>Y</label>
        <label className={styles.rightAlignLabel}>Z</label>
      </div>
      <div className={styles.vector3Row}>
        <input
          className={styles.rightAlignLabel}
          placeholder="0"
          onChange={props.onXChange}
        ></input>
        <input
          className={styles.rightAlignLabel}
          placeholder="0"
          onChange={props.onYChange}
        ></input>
        <input
          className={styles.rightAlignLabel}
          placeholder="0"
          onChange={props.onZChange}
        ></input>
      </div>
    </div>
  );
}
