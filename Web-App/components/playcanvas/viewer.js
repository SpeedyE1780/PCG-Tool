import Game from "./game";
import styles from "../../styles/Home.module.css";

export default function Viewer({ children }) {
  return (
    <div className={styles.viewer}>
      <div className={styles.viewerParams}>{children}</div>
      <Game></Game>
    </div>
  );
}
