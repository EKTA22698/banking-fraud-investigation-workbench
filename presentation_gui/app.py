from pathlib import Path
import subprocess
import tkinter as tk
from tkinter import messagebox

try:
    from PIL import Image, ImageTk
    PIL_AVAILABLE = True
except ImportError:
    PIL_AVAILABLE = False


# ============================================================
# PATHS
# ============================================================

ROOT = Path(__file__).resolve().parent.parent
FIGURES = ROOT / "docs" / "figures"
EXECUTABLE = ROOT / "build" / "fraud_workbench.exe"


# ============================================================
# THEME
# ============================================================

BG = "#08111F"
SIDEBAR = "#0D1726"
CARD = "#121E2F"
CARD_ALT = "#162437"
TEXT = "#F3F7FC"
MUTED = "#91A4BA"
ACCENT = "#36D399"
BLUE = "#60A5FA"
WARNING = "#FBBF24"
DANGER = "#F87171"
BORDER = "#26374B"

FONT = "Segoe UI"


# ============================================================
# MAIN APPLICATION
# ============================================================

class FraudWorkbenchGUI(tk.Tk):

    def __init__(self):
        super().__init__()

        self.title(
            "Banking Transaction Fraud Investigation Workbench"
        )

        self.geometry("1400x820")
        self.minsize(1150, 700)

        self.configure(bg=BG)

        self.loaded_images = []

        self.create_layout()
        self.show_dashboard()


    # ========================================================
    # LAYOUT
    # ========================================================

    def create_layout(self):

        self.sidebar = tk.Frame(
            self,
            bg=SIDEBAR,
            width=230
        )

        self.sidebar.pack(
            side="left",
            fill="y"
        )

        self.sidebar.pack_propagate(False)


        brand = tk.Label(
            self.sidebar,
            text="FRAUD\nWORKBENCH",
            bg=SIDEBAR,
            fg=TEXT,
            font=(FONT, 20, "bold"),
            justify="left"
        )

        brand.pack(
            anchor="w",
            padx=25,
            pady=(28, 6)
        )


        subtitle = tk.Label(
            self.sidebar,
            text="DAA Investigation Platform",
            bg=SIDEBAR,
            fg=MUTED,
            font=(FONT, 9)
        )

        subtitle.pack(
            anchor="w",
            padx=25,
            pady=(0, 30)
        )


        self.add_nav_button(
            "Dashboard",
            self.show_dashboard
        )

        self.add_nav_button(
            "Fraud Analysis",
            self.show_fraud
        )

        self.add_nav_button(
            "Algorithm Explorer",
            self.show_algorithms
        )

        self.add_nav_button(
            "Benchmarks",
            self.show_benchmarks
        )

        self.add_nav_button(
            "Project Evidence",
            self.show_evidence
        )


        tk.Frame(
            self.sidebar,
            bg=SIDEBAR
        ).pack(
            expand=True,
            fill="both"
        )


        launch = tk.Button(
            self.sidebar,
            text="Launch C Workbench",
            command=self.launch_workbench,
            bg=ACCENT,
            fg="#04130D",
            activebackground="#6EE7B7",
            activeforeground="#04130D",
            relief="flat",
            bd=0,
            cursor="hand2",
            font=(FONT, 10, "bold"),
            padx=12,
            pady=12
        )

        launch.pack(
            fill="x",
            padx=20,
            pady=(0, 12)
        )


        version = tk.Label(
            self.sidebar,
            text="Core Release  v1.0.0",
            bg=SIDEBAR,
            fg=MUTED,
            font=(FONT, 8)
        )

        version.pack(
            pady=(0, 20)
        )


        # MAIN AREA

        self.main = tk.Frame(
            self,
            bg=BG
        )

        self.main.pack(
            side="left",
            expand=True,
            fill="both"
        )


    def add_nav_button(
        self,
        text,
        command
    ):

        button = tk.Button(
            self.sidebar,
            text=text,
            command=command,
            anchor="w",
            bg=SIDEBAR,
            fg=TEXT,
            activebackground=CARD_ALT,
            activeforeground=TEXT,
            relief="flat",
            bd=0,
            cursor="hand2",
            font=(FONT, 10),
            padx=25,
            pady=13
        )

        button.pack(
            fill="x"
        )


    # ========================================================
    # HELPERS
    # ========================================================

    def clear_main(self):

        for widget in self.main.winfo_children():
            widget.destroy()

        self.loaded_images.clear()


    def page_header(
        self,
        title,
        subtitle
    ):

        header = tk.Frame(
            self.main,
            bg=BG
        )

        header.pack(
            fill="x",
            padx=35,
            pady=(28, 20)
        )


        left = tk.Frame(
            header,
            bg=BG
        )

        left.pack(
            side="left"
        )


        tk.Label(
            left,
            text=title,
            bg=BG,
            fg=TEXT,
            font=(FONT, 24, "bold")
        ).pack(
            anchor="w"
        )


        tk.Label(
            left,
            text=subtitle,
            bg=BG,
            fg=MUTED,
            font=(FONT, 10)
        ).pack(
            anchor="w",
            pady=(4, 0)
        )


        status = tk.Label(
            header,
            text="●  SYSTEM READY",
            bg=BG,
            fg=ACCENT,
            font=(FONT, 9, "bold")
        )

        status.pack(
            side="right",
            pady=12
        )


    def metric_card(
        self,
        parent,
        title,
        value,
        detail="",
        color=TEXT
    ):

        card = tk.Frame(
            parent,
            bg=CARD,
            highlightbackground=BORDER,
            highlightthickness=1
        )


        tk.Label(
            card,
            text=title.upper(),
            bg=CARD,
            fg=MUTED,
            font=(FONT, 8, "bold")
        ).pack(
            anchor="w",
            padx=18,
            pady=(15, 4)
        )


        tk.Label(
            card,
            text=value,
            bg=CARD,
            fg=color,
            font=(FONT, 22, "bold")
        ).pack(
            anchor="w",
            padx=18
        )


        if detail:

            tk.Label(
                card,
                text=detail,
                bg=CARD,
                fg=MUTED,
                font=(FONT, 8)
            ).pack(
                anchor="w",
                padx=18,
                pady=(3, 15)
            )

        else:

            tk.Frame(
                card,
                bg=CARD,
                height=15
            ).pack()


        return card


    def section_title(
        self,
        parent,
        text
    ):

        tk.Label(
            parent,
            text=text,
            bg=BG,
            fg=TEXT,
            font=(FONT, 14, "bold")
        ).pack(
            anchor="w",
            pady=(5, 12)
        )


    # ========================================================
    # DASHBOARD
    # ========================================================

    def show_dashboard(self):

        self.clear_main()

        self.page_header(
            "Investigation Dashboard",
            "Verified project metrics and system status"
        )


        cards = tk.Frame(
            self.main,
            bg=BG
        )

        cards.pack(
            fill="x",
            padx=35
        )


        values = [
            (
                "PaySim Transactions",
                "6.36M",
                "6,362,620 valid records",
                BLUE
            ),
            (
                "Automated Tests",
                "48 / 48",
                "Overall result: PASS",
                ACCENT
            ),
            (
                "Recall",
                "99.73%",
                "PaySim threshold = 50",
                ACCENT
            ),
            (
                "Precision",
                "0.38%",
                "High-recall triage heuristic",
                WARNING
            )
        ]


        for index, data in enumerate(values):

            card = self.metric_card(
                cards,
                *data
            )

            card.grid(
                row=0,
                column=index,
                sticky="nsew",
                padx=(0 if index == 0 else 8, 0)
            )

            cards.grid_columnconfigure(
                index,
                weight=1
            )


        content = tk.Frame(
            self.main,
            bg=BG
        )

        content.pack(
            expand=True,
            fill="both",
            padx=35,
            pady=25
        )


        left = tk.Frame(
            content,
            bg=CARD,
            highlightbackground=BORDER,
            highlightthickness=1
        )

        left.pack(
            side="left",
            expand=True,
            fill="both",
            padx=(0, 10)
        )


        tk.Label(
            left,
            text="PROJECT STATUS",
            bg=CARD,
            fg=MUTED,
            font=(FONT, 9, "bold")
        ).pack(
            anchor="w",
            padx=22,
            pady=(20, 15)
        )


        status_items = [
            ("Core C Workbench", "READY"),
            ("Algorithm Coverage", "COMPLETE"),
            ("Automated Regression", "48/48 PASS"),
            ("Full PaySim Loader", "VERIFIED"),
            ("Complexity Analysis", "DOCUMENTED"),
            ("Release", "v1.0.0")
        ]


        for label, value in status_items:

            row = tk.Frame(
                left,
                bg=CARD
            )

            row.pack(
                fill="x",
                padx=22,
                pady=7
            )


            tk.Label(
                row,
                text=label,
                bg=CARD,
                fg=TEXT,
                font=(FONT, 10)
            ).pack(
                side="left"
            )


            tk.Label(
                row,
                text=value,
                bg=CARD,
                fg=ACCENT,
                font=(FONT, 9, "bold")
            ).pack(
                side="right"
            )


        right = tk.Frame(
            content,
            bg=CARD,
            highlightbackground=BORDER,
            highlightthickness=1
        )

        right.pack(
            side="left",
            expand=True,
            fill="both",
            padx=(10, 0)
        )


        tk.Label(
            right,
            text="INVESTIGATION WORKFLOW",
            bg=CARD,
            fg=MUTED,
            font=(FONT, 9, "bold")
        ).pack(
            anchor="w",
            padx=22,
            pady=(20, 15)
        )


        workflow = [
            "01   Load banking dataset",
            "02   Score and triage transactions",
            "03   Search suspicious patterns",
            "04   Analyze evidence network",
            "05   Optimize investigation resources",
            "06   Benchmark and validate results"
        ]


        for item in workflow:

            tk.Label(
                right,
                text=item,
                bg=CARD,
                fg=TEXT,
                font=(FONT, 10),
                anchor="w"
            ).pack(
                fill="x",
                padx=22,
                pady=7
            )


    # ========================================================
    # FRAUD ANALYSIS
    # ========================================================

    def show_fraud(self):

        self.clear_main()

        self.page_header(
            "Fraud Analysis",
            "PaySim ground-truth evaluation at risk threshold 50"
        )


        cards = tk.Frame(
            self.main,
            bg=BG
        )

        cards.pack(
            fill="x",
            padx=35
        )


        data = [
            (
                "Recall",
                "99.73%",
                "Fraud cases detected",
                ACCENT
            ),
            (
                "Precision",
                "0.38%",
                "Alert precision",
                WARNING
            ),
            (
                "F1 Score",
                "0.76%",
                "Precision/recall balance",
                BLUE
            ),
            (
                "Dataset",
                "6.36M",
                "PaySim transactions",
                TEXT
            )
        ]


        for i, item in enumerate(data):

            card = self.metric_card(
                cards,
                *item
            )

            card.grid(
                row=0,
                column=i,
                sticky="nsew",
                padx=(0 if i == 0 else 8, 0)
            )

            cards.grid_columnconfigure(
                i,
                weight=1
            )


        panel = tk.Frame(
            self.main,
            bg=CARD,
            highlightbackground=BORDER,
            highlightthickness=1
        )

        panel.pack(
            expand=True,
            fill="both",
            padx=35,
            pady=25
        )


        tk.Label(
            panel,
            text="Interpretation",
            bg=CARD,
            fg=TEXT,
            font=(FONT, 16, "bold")
        ).pack(
            anchor="w",
            padx=25,
            pady=(24, 10)
        )


        explanation = (
            "The current fraud scorer is intentionally presented as "
            "an investigation-triage heuristic rather than an autonomous "
            "banking decision system.\n\n"
            "At threshold 50 it achieves very high recall, identifying "
            "almost all ground-truth PaySim fraud cases, but precision "
            "remains low because many legitimate transactions are also "
            "flagged.\n\n"
            "This makes the output suitable for prioritizing analyst "
            "review while demonstrating the trade-off between false "
            "positives and false negatives."
        )


        tk.Label(
            panel,
            text=explanation,
            bg=CARD,
            fg=TEXT,
            justify="left",
            wraplength=850,
            font=(FONT, 11),
            anchor="nw"
        ).pack(
            anchor="w",
            padx=25,
            pady=10
        )


        warning = tk.Frame(
            panel,
            bg=CARD_ALT
        )

        warning.pack(
            fill="x",
            padx=25,
            pady=20
        )


        tk.Label(
            warning,
            text="Responsible Use",
            bg=CARD_ALT,
            fg=WARNING,
            font=(FONT, 10, "bold")
        ).pack(
            anchor="w",
            padx=16,
            pady=(13, 4)
        )


        tk.Label(
            warning,
            text=(
                "A suspicious score is an investigation signal, "
                "not proof that a customer committed fraud."
            ),
            bg=CARD_ALT,
            fg=TEXT,
            font=(FONT, 10)
        ).pack(
            anchor="w",
            padx=16,
            pady=(0, 13)
        )


    # ========================================================
    # ALGORITHMS
    # ========================================================

    def show_algorithms(self):

        self.clear_main()

        self.page_header(
            "Algorithm Explorer",
            "DAA syllabus coverage integrated into the workbench"
        )


        container = tk.Frame(
            self.main,
            bg=BG
        )

        container.pack(
            expand=True,
            fill="both",
            padx=35,
            pady=(0, 30)
        )


        categories = [
            (
                "Divide & Conquer",
                "Maximum Subarray\nFast Power\nCelebrity\nClassical vs Strassen"
            ),
            (
                "Greedy",
                "Activity Selection\nInterval Partitioning\nFractional Knapsack\nHuffman"
            ),
            (
                "Dynamic Programming",
                "0/1 Knapsack\nMatrix Chain\nLCS\nOptimal BST\nBounded TSP"
            ),
            (
                "Backtracking",
                "N-Queens\nSubset Sum\n0/1 Knapsack"
            ),
            (
                "Graph & Network",
                "Dijkstra\nBellman-Ford\nFloyd-Warshall\nPrim / Kruskal\nMax Flow / Matching"
            ),
            (
                "String & Number Theory",
                "Naive\nRabin-Karp\nFinite Automaton\nKMP\nCRT"
            )
        ]


        for i, (title, algorithms) in enumerate(categories):

            card = tk.Frame(
                container,
                bg=CARD,
                highlightbackground=BORDER,
                highlightthickness=1
            )

            row = i // 3
            column = i % 3

            card.grid(
                row=row,
                column=column,
                sticky="nsew",
                padx=7,
                pady=7
            )


            container.grid_columnconfigure(
                column,
                weight=1
            )

            container.grid_rowconfigure(
                row,
                weight=1
            )


            tk.Label(
                card,
                text=title,
                bg=CARD,
                fg=BLUE,
                font=(FONT, 13, "bold")
            ).pack(
                anchor="w",
                padx=18,
                pady=(18, 10)
            )


            tk.Label(
                card,
                text=algorithms,
                bg=CARD,
                fg=TEXT,
                justify="left",
                font=(FONT, 10),
                anchor="nw"
            ).pack(
                anchor="w",
                padx=18,
                pady=(0, 18)
            )


    # ========================================================
    # BENCHMARKS
    # ========================================================

    def show_benchmarks(self):

        self.clear_main()

        self.page_header(
            "Benchmark Evidence",
            "Recorded PaySim scalability and fraud-quality figures"
        )


        controls = tk.Frame(
            self.main,
            bg=BG
        )

        controls.pack(
            fill="x",
            padx=35,
            pady=(0, 15)
        )


        buttons = [
            (
                "Runtime",
                "paysim_runtime.png"
            ),
            (
                "Memory",
                "paysim_memory.png"
            ),
            (
                "Fraud Quality",
                "paysim_quality.png"
            )
        ]


        self.chart_panel = tk.Frame(
            self.main,
            bg=CARD,
            highlightbackground=BORDER,
            highlightthickness=1
        )

        self.chart_panel.pack(
            expand=True,
            fill="both",
            padx=35,
            pady=(0, 30)
        )


        for label, filename in buttons:

            tk.Button(
                controls,
                text=label,
                command=lambda f=filename:
                    self.display_chart(f),
                bg=CARD,
                fg=TEXT,
                activebackground=CARD_ALT,
                activeforeground=TEXT,
                relief="flat",
                bd=0,
                cursor="hand2",
                font=(FONT, 9, "bold"),
                padx=18,
                pady=9
            ).pack(
                side="left",
                padx=(0, 8)
            )


        self.display_chart(
            "paysim_runtime.png"
        )


    def display_chart(
        self,
        filename
    ):

        for widget in self.chart_panel.winfo_children():
            widget.destroy()


        path = FIGURES / filename


        if not path.exists():

            tk.Label(
                self.chart_panel,
                text=f"Figure not found:\n{path}",
                bg=CARD,
                fg=DANGER,
                font=(FONT, 11)
            ).pack(
                expand=True
            )

            return


        if not PIL_AVAILABLE:

            tk.Label(
                self.chart_panel,
                text=(
                    "Pillow is required to display PNG figures.\n\n"
                    f"Figure available at:\n{path}"
                ),
                bg=CARD,
                fg=TEXT,
                font=(FONT, 11)
            ).pack(
                expand=True
            )

            return


        image = Image.open(path)

        image.thumbnail(
            (900, 540)
        )

        photo = ImageTk.PhotoImage(
            image
        )

        self.loaded_images.append(
            photo
        )


        tk.Label(
            self.chart_panel,
            image=photo,
            bg=CARD
        ).pack(
            expand=True,
            padx=20,
            pady=20
        )


    # ========================================================
    # EVIDENCE
    # ========================================================

    def show_evidence(self):

        self.clear_main()

        self.page_header(
            "Project Evidence",
            "Verified implementation and evaluation checkpoints"
        )


        container = tk.Frame(
            self.main,
            bg=BG
        )

        container.pack(
            expand=True,
            fill="both",
            padx=35,
            pady=(0, 30)
        )


        evidence = [
            (
                "Automated Testing",
                "48 / 48 PASS",
                "Deterministic algorithm oracles and cross-checks."
            ),
            (
                "PaySim Loading",
                "6,362,620",
                "Full public fraud dataset loaded dynamically."
            ),
            (
                "Scalability",
                "205 ms",
                "Recorded fraud-analysis benchmark at full PaySim scale."
            ),
            (
                "Memory Evidence",
                "2,281.52 MB",
                "Approximate transaction-array memory at full scale."
            ),
            (
                "Complexity Theory",
                "COMPLETE",
                "O, Ω, Θ, recurrences, Master Theorem and comparisons."
            ),
            (
                "Complexity Classes",
                "DOCUMENTED",
                "P, NP, NP-Complete, NP-Hard and polynomial reduction."
            )
        ]


        for i, (title, value, detail) in enumerate(evidence):

            card = self.metric_card(
                container,
                title,
                value,
                detail,
                ACCENT if i < 2 else TEXT
            )

            row = i // 3
            column = i % 3

            card.grid(
                row=row,
                column=column,
                sticky="nsew",
                padx=7,
                pady=7
            )

            container.grid_columnconfigure(
                column,
                weight=1
            )

            container.grid_rowconfigure(
                row,
                weight=1
            )


    # ========================================================
    # C WORKBENCH
    # ========================================================

    def launch_workbench(self):

        if not EXECUTABLE.exists():

            messagebox.showerror(
                "Executable Not Found",
                (
                    "The C workbench has not been built.\n\n"
                    "Run:\n"
                    "cmake --preset windows-ucrt64\n"
                    "cmake --build --preset windows-ucrt64"
                )
            )

            return


        try:

            subprocess.Popen(
                [
                    "cmd",
                    "/k",
                    str(EXECUTABLE)
                ],
                cwd=str(ROOT),
                creationflags=(
                    subprocess.CREATE_NEW_CONSOLE
                    if hasattr(
                        subprocess,
                        "CREATE_NEW_CONSOLE"
                    )
                    else 0
                )
            )

        except Exception as error:

            messagebox.showerror(
                "Launch Failed",
                str(error)
            )


# ============================================================
# ENTRY POINT
# ============================================================

if __name__ == "__main__":

    app = FraudWorkbenchGUI()
    app.mainloop()