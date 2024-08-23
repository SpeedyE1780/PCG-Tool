import PCGHeader from "./pcgHeader";

export default function PCGMain({ children }) {
  return (
    <>
      <PCGHeader></PCGHeader>
      {children}
    </>
  );
}
