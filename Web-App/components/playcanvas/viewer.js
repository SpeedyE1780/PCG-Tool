import Game from "./game";
import styles from "../../styles/Home.module.css";

export default function Viewer({ children, ...props }) {
  return (
    <div className={styles.viewer}>
      <div className={styles.viewerParams}>
        {children}
        <label>Generated JSON</label>
        <textarea
          className={styles.viewerResponseArea}
          value={props.responseJSON}
          readOnly={true}
        ></textarea>
      </div>
      <Game></Game>
    </div>
  );
}
