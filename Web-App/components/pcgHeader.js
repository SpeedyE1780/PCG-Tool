import Link from "next/link";
import styles from "../styles/Home.module.css";

export default function PCGHeader() {
  return (
    <header className={styles.pcgHeader}>
      <Link href="/" className={styles.pcgHeaderLink}>
        Home
      </Link>
      <Link href="/combination" className={styles.pcgHeaderLink}>
        Combination
      </Link>
      <Link href="/maze" className={styles.pcgHeaderLink}>
        Maze
      </Link>
      <Link href="/multiDimensionGeneration" className={styles.pcgHeaderLink}>
        Multi Dimension
      </Link>
      <Link href="/simpleGeneration" className={styles.pcgHeaderLink}>
        Simple Dimension
      </Link>
      <Link href="/waveFunctionCollapse" className={styles.pcgHeaderLink}>
        Wave Function Collapse Dimension
      </Link>
      <Link href="/waveFunctionCollapseGrid2D" className={styles.pcgHeaderLink}>
        Grid 2D Wave Function Collapse Dimension
      </Link>
      <Link href="/waveFunctionCollapseGrid3D" className={styles.pcgHeaderLink}>
        Grid 3D Wave Function Collapse Dimension
      </Link>
    </header>
  );
}
